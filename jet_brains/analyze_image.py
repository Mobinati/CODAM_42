"""
Command-line starter: create a saliency map for a single screenshot.

Usage:
    python analyze_image.py screenshot.png

This script creates screenshot_saliency.png next to the input image.
"""

import sys
from pathlib import Path

import cv2


def main() -> int:
    # Require exactly one image path argument.
    if len(sys.argv) != 2:
        print("Usage: python analyze_image.py path/to/screenshot.png")
        return 1

    input_path = Path(sys.argv[1])

    # Load the image with OpenCV. None means the path could not be read.
    image = cv2.imread(str(input_path))
    if image is None:
        print(f"Could not read image: {input_path}")
        return 1

    # This model is included in opencv-contrib-python.
    if not hasattr(cv2, "saliency"):
        print("Missing cv2.saliency. Install opencv-contrib-python.")
        return 1

    # Create a spectral-residual saliency model and calculate a map.
    model = cv2.saliency.StaticSaliencySpectralResidual_create()
    success, saliency = model.computeSaliency(image)
    if not success:
        print("Could not calculate saliency.")
        return 1

    # Save both a grayscale map and a colour overlay.
    saliency_u8 = (saliency.clip(0, 1) * 255).astype("uint8")
    heatmap = cv2.applyColorMap(saliency_u8, cv2.COLORMAP_JET)
    overlay = cv2.addWeighted(image, 0.60, heatmap, 0.40, 0)

    output_path = input_path.with_name(input_path.stem + "_saliency.png")
    if not cv2.imwrite(str(output_path), overlay):
        print(f"Could not save output: {output_path}")
        return 1

    print(f"Saved saliency overlay to: {output_path}")
    print("Reminder: this predicts generic image saliency, not actual human gaze.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
