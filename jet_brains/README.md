# JetBrains IDE UX Validation — Starter PoC

This starter project is for learning and experimentation. It is not a validated
usability assessment tool.

## What it currently does

- Accepts a screenshot in a Streamlit web app.
- Tries to generate a generic saliency map with OpenCV.
- Calculates two simple whole-image statistics and explains their limitations.
- Optionally attempts to run a Hugging Face vision-language model.
- Lets you download the heuristic findings and raw optional model output.

## 1. Create a virtual environment

Linux/macOS:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
```

## 2. Install packages

```bash
pip install -r requirements.txt
```

The dependencies for the optional vision-language model are large. If you want
to begin with the simpler parts, install only:

```bash
pip install streamlit pillow numpy opencv-contrib-python pandas
```

## 3. Run the app

```bash
streamlit run app.py
```

Streamlit prints a local address (usually http://localhost:8501). Open it in
your browser and upload an IDE screenshot.

## 4. Run only the saliency script

```bash
python analyze_image.py path/to/screenshot.png
```

It saves a file ending in `_saliency.png` beside the input.

## Important scientific limitations

1. Generic saliency is not the same as eye-tracking or task-dependent attention.
2. Whole-image contrast statistics cannot identify a specific problematic UI element.
3. A vision-language model can hallucinate UI elements and UX issues.
4. Validate recommendations with UX researchers or human study data.
5. Do not upload private company screenshots or confidential data to external
   services without permission.

## Suggested next steps

1. Test with a small set of public or synthetic IDE screenshots.
2. Keep notes in `evaluation_template.csv`.
3. Compare the model output with human review.
4. Inspect the UEyes dataset and its licence/terms before using it.
5. Only then consider UI-element detection, a better saliency model, or eye-tracking
   validation.

## Troubleshooting

- If `cv2.saliency` is missing, check that `opencv-contrib-python` is installed.
- Do not install `opencv-python` and `opencv-contrib-python` together in the same
  environment; they both provide the `cv2` module.
- The optional VLM may require a recent Transformers version and substantial RAM
  or GPU memory. It is optional; the base app can run without it.
