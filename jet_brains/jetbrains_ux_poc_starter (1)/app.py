"""
Starter PoC for the JetBrains AI-Powered UX Validation project.

What it does:
1. Accepts an IDE screenshot.
2. Creates a visual-saliency heatmap (if OpenCV's saliency module is installed).
3. Runs transparent, rule-based checks on image properties.
4. Optionally asks a vision-language model to describe possible UX issues.

Important:
- A saliency map is NOT a measurement of a real person's gaze.
- The built-in checks are heuristics, not proof of usability problems.
- The optional AI model can make mistakes; verify its findings.
"""

import io
import json
from typing import Any

import cv2
import numpy as np
import pandas as pd
import streamlit as st
from PIL import Image, ImageStat


def pil_to_bgr(image: Image.Image) -> np.ndarray:
    """Convert a PIL image into OpenCV's BGR colour format."""
    rgb = np.array(image.convert("RGB"))
    return cv2.cvtColor(rgb, cv2.COLOR_RGB2BGR)


def make_saliency_map(image: Image.Image) -> tuple[np.ndarray | None, str]:
    """
    Try OpenCV's Static Saliency Spectral Residual model.

    Returns:
        A grayscale saliency map (values 0..255), or None if unavailable,
        plus a message describing what happened.
    """
    bgr = pil_to_bgr(image)

    # The saliency API is supplied by opencv-contrib-python.
    if not hasattr(cv2, "saliency"):
        return None, (
            "OpenCV saliency module is unavailable. Install "
            "opencv-contrib-python and restart the app."
        )

    model = cv2.saliency.StaticSaliencySpectralResidual_create()
    success, saliency = model.computeSaliency(bgr)

    if not success:
        return None, "OpenCV could not calculate a saliency map."

    # Convert floating-point scores to an 8-bit image for display.
    saliency_u8 = np.clip(saliency * 255, 0, 255).astype(np.uint8)
    return saliency_u8, (
        "Generated using OpenCV Spectral Residual saliency. "
        "This is a generic image-saliency baseline, not an IDE-trained gaze model."
    )


def overlay_heatmap(image: Image.Image, saliency: np.ndarray) -> Image.Image:
    """Colourise the saliency map and blend it over the original screenshot."""
    original_bgr = pil_to_bgr(image)
    heatmap_bgr = cv2.applyColorMap(saliency, cv2.COLORMAP_JET)
    blended = cv2.addWeighted(original_bgr, 0.60, heatmap_bgr, 0.40, 0)
    blended_rgb = cv2.cvtColor(blended, cv2.COLOR_BGR2RGB)
    return Image.fromarray(blended_rgb)


def run_heuristic_checks(image: Image.Image) -> list[dict[str, str]]:
    """
    Run simple, explainable checks based on whole-image properties.

    These checks deliberately avoid claiming that a specific UI element is
    confusing: this version does not yet detect UI elements or understand tasks.
    """
    rgb = np.array(image.convert("RGB"))
    gray = cv2.cvtColor(rgb, cv2.COLOR_RGB2GRAY)

    # Standard deviation is a rough measure of how much pixel brightness varies.
    brightness_variation = float(np.std(gray))

    # Estimate average contrast using the difference between bright and dark
    # grayscale percentiles. This is only a global image-level statistic.
    p5, p95 = np.percentile(gray, [5, 95])
    contrast_range = float(p95 - p5)

    findings = []

    if contrast_range < 100:
        findings.append({
            "type": "Heuristic observation",
            "observation": "The screenshot has a relatively narrow global brightness range.",
            "possible_issue": "Some controls or text might have limited visual contrast.",
            "recommendation": "Inspect text and control contrast individually; do not rely on this global score alone.",
            "confidence": "Low",
            "evidence": f"5th–95th percentile grayscale range: {contrast_range:.1f}/255."
        })
    else:
        findings.append({
            "type": "Heuristic observation",
            "observation": "The screenshot contains a broad range of brightness values.",
            "possible_issue": "This does not by itself establish whether the visual hierarchy is good or bad.",
            "recommendation": "Inspect the screenshot and task context; check the contrast of important elements individually.",
            "confidence": "Low",
            "evidence": f"5th–95th percentile grayscale range: {contrast_range:.1f}/255."
        })

    findings.append({
        "type": "Image statistic",
        "observation": "The image has measurable variation in pixel brightness.",
        "possible_issue": "A whole-image statistic cannot identify which UI element attracts attention.",
        "recommendation": "Use this only as a baseline; add UI-element detection and human-validated data in later versions.",
        "confidence": "Low",
        "evidence": f"Grayscale standard deviation: {brightness_variation:.1f}."
    })
    return findings


def run_optional_vlm(image: Image.Image, task_context: str) -> tuple[str | None, str]:
    """
    Optionally ask a pretrained vision-language model for a first-pass critique.

    The model is downloaded on first use and may require substantial RAM/VRAM.
    This uses Hugging Face Transformers' image-text-to-text pipeline.
    If the model or hardware is incompatible, the app returns an explanatory
    message instead of crashing.
    """
    try:
        from transformers import pipeline

        model_name = "Qwen/Qwen2.5-VL-3B-Instruct"
        # Cache the model between Streamlit reruns.
        @st.cache_resource(show_spinner="Loading the vision-language model...")
        def load_model():
            return pipeline(
                task="image-text-to-text",
                model=model_name,
                device_map="auto"
            )

        model = load_model()

        prompt = (
            "You are assisting a UX researcher evaluating a screenshot of an "
            "IntelliJ-based IDE. Identify only issues supported by visible evidence. "
            "Separate directly observable facts from hypotheses about user attention. "
            "Do not claim to know where a real user looked. For each finding provide: "
            "observation, possible usability concern, concrete recommendation, and "
            "confidence (low/medium/high). If evidence is insufficient, say so. "
            f"Developer task context: {task_context or 'Not provided.'}"
        )

        # The pipeline expects a conversational message containing image + text.
        messages = [{
            "role": "user",
            "content": [
                {"type": "image", "image": image},
                {"type": "text", "text": prompt}
            ]
        }]

        result = model(text=messages, max_new_tokens=500)
        return json.dumps(result, indent=2, ensure_ascii=False, default=str), (
            f"Model: {model_name}. Treat output as unverified hypotheses."
        )
    except Exception as exc:
        return None, (
            "The optional vision-language model did not run. This can happen because "
            "of model compatibility, memory, or package versions. The rest of the "
            f"prototype can still be used. Technical detail: {type(exc).__name__}: {exc}"
        )


st.set_page_config(page_title="IDE UX Validation PoC", layout="wide")
st.title("AI-Powered IDE UX Validation — Starter PoC")
st.caption(
    "Research prototype only. Saliency and AI outputs are hypotheses, not evidence "
    "of actual user gaze or validated usability problems."
)

uploaded = st.file_uploader(
    "Upload an IDE screenshot (PNG or JPEG)",
    type=["png", "jpg", "jpeg"]
)
task_context = st.text_input(
    "What is the developer trying to do? (optional)",
    placeholder="Example: Find and fix a compilation error"
)
use_vlm = st.checkbox(
    "Also run the optional vision-language model (downloads a large model on first use)",
    value=False
)

if uploaded:
    try:
        image = Image.open(io.BytesIO(uploaded.getvalue())).convert("RGB")
    except Exception:
        st.error("The uploaded file could not be read as an image.")
        st.stop()

    st.subheader("Input screenshot")
    st.image(image, caption=f"Input: {image.width} × {image.height}", use_container_width=True)

    if st.button("Analyze screenshot", type="primary"):
        with st.spinner("Analyzing screenshot..."):
            findings = run_heuristic_checks(image)
            saliency, saliency_message = make_saliency_map(image)

        left, right = st.columns(2)
        with left:
            st.subheader("Visual attention baseline")
            if saliency is not None:
                st.image(overlay_heatmap(image, saliency),
                         caption="Saliency overlay (generic baseline)",
                         use_container_width=True)
                st.image(saliency, caption="Raw saliency map", use_container_width=True)
            st.info(saliency_message)

        with right:
            st.subheader("Explainable baseline checks")
            st.dataframe(pd.DataFrame(findings), use_container_width=True, hide_index=True)

        st.download_button(
            "Download heuristic findings as JSON",
            data=json.dumps(findings, indent=2, ensure_ascii=False),
            file_name="heuristic_findings.json",
            mime="application/json"
        )

        if use_vlm:
            with st.spinner("Running the optional vision-language model..."):
                vlm_text, vlm_message = run_optional_vlm(image, task_context)
            st.subheader("Vision-language model output")
            st.info(vlm_message)
            if vlm_text:
                st.text_area("Raw model output (review critically)", vlm_text, height=300)
                st.download_button(
                    "Download model output",
                    data=vlm_text,
                    file_name="vlm_output.json",
                    mime="application/json"
                )
else:
    st.write("Upload a screenshot to begin. Try a public/demo IDE screenshot first.")
