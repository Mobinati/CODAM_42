import json
import glob
import os

import numpy as np
import matplotlib.pyplot as plt

from PIL import Image
from scipy.ndimage import gaussian_filter


# --------------------------------------------------
# 1. Load the JSON data
# --------------------------------------------------

with open("responses.json", "r") as file:
    data = json.load(file)

print("JSON data loaded successfully.")
print("Number of participants:", len(data))


# # --------------------------------------------------
# # 2. Find all screenshots
# # --------------------------------------------------

image_paths = (
    glob.glob("./screenshots/*.jpeg")
    + glob.glob("./screenshots/*.jpg")
    + glob.glob("./screenshots/*.png")
)

if not image_paths:
    raise FileNotFoundError("No screenshots found!")

screenshots = {}

for image_path in image_paths:

    filename = os.path.basename(image_path)

    # Extract the ID between square brackets.
    screen_id = filename.split("]")[0].replace("[", "")

    # Convert the ID to match the JSON format.
    screen_id = screen_id.replace("-", ":")

    screenshots[screen_id] = image_path

print("\nScreenshots found:")

for screen_id, path in screenshots.items():
    print(screen_id, "->", path)

# --------------------------------------------------
# 3. Extract clicks from all participants
# --------------------------------------------------

all_clicks = {}

for participant_id, participant_data in data.items():

    answers = participant_data.get("answers", {})

    for answer_id, answer_data in answers.items():

        clicks_by_screen = answer_data.get("clicks", {})

        for screen_id, clicks in clicks_by_screen.items():

            if screen_id not in all_clicks:
                all_clicks[screen_id] = []

            for click in clicks:

                x = click.get("frame_click_x")
                y = click.get("frame_click_y")

                if x is None or y is None:
                    continue

                all_clicks[screen_id].append({
                    "x": float(x),
                    "y": float(y),
                    "is_hotspot": click.get(
                        "is_hotspot_click", False
                    )
                })


# --------------------------------------------------
# 4. Create output directory
# --------------------------------------------------

output_dir = "./heatmaps"

os.makedirs(output_dir, exist_ok=True)


# --------------------------------------------------
# 5. Generate heatmaps for each screenshot
# --------------------------------------------------

for screen_id, image_path in screenshots.items():

    print("\nProcessing screen:", screen_id)

    image = Image.open(image_path).convert("RGB")

    width, height = image.size

    # Get clicks belonging to this screen.
    clicks = all_clicks.get(screen_id, [])

    # Extract coordinates.
    x_all = [click["x"] for click in clicks]
    y_all = [click["y"] for click in clicks]

    # Extract only hotspot clicks.
    hotspot_clicks = [
        click for click in clicks
        if click["is_hotspot"]
    ]

    x_hotspot = [click["x"] for click in hotspot_clicks]
    y_hotspot = [click["y"] for click in hotspot_clicks]

    print("Image size:", width, "x", height)
    print("Total clicks:", len(x_all))
    print("Hotspot clicks:", len(x_hotspot))

    # --------------------------------------------------
    # 5A. Generate heatmap with all clicks
    # --------------------------------------------------

    heatmap, _, _ = np.histogram2d(
        y_all,
        x_all,
        bins=[height, width],
        range=[[0, height], [0, width]]
    )

    # Smooth the heatmap using a Gaussian filter.
    heatmap = gaussian_filter(heatmap, sigma=20)

    fig, ax = plt.subplots(figsize=(12, 7))

    ax.imshow(image)
    ax.imshow(
        heatmap,
        cmap="hot",
        alpha=0.5,
        extent=[0, width, height, 0]
    )

    ax.set_title(
        f"All Clicks - Screen {screen_id}"
    )

    ax.axis("off")

    plt.tight_layout()

    plt.savefig(
        os.path.join(
            output_dir,
            f"{screen_id}_all_clicks.png"
        ),
        dpi=150
    )

    plt.close()


    # --------------------------------------------------
    # 5B. Generate heatmap with hotspot clicks only
    # --------------------------------------------------

    heatmap_hotspot, _, _ = np.histogram2d(
        y_hotspot,
        x_hotspot,
        bins=[height, width],
        range=[[0, height], [0, width]]
    )

    heatmap_hotspot = gaussian_filter(
        heatmap_hotspot,
        sigma=20
    )

    fig, ax = plt.subplots(figsize=(12, 7))

    ax.imshow(image)
    ax.imshow(
        heatmap_hotspot,
        cmap="hot",
        alpha=0.5,
        extent=[0, width, height, 0]
    )

    ax.set_title(
        f"Hotspot Clicks - Screen {screen_id}"
    )

    ax.axis("off")

    plt.tight_layout()

    plt.savefig(
        os.path.join(
            output_dir,
            f"{screen_id}_hotspot_clicks.png"
        ),
        dpi=150
    )

    plt.close()


print("\nAll heatmaps generated successfully!")
print("Output directory:", output_dir)
