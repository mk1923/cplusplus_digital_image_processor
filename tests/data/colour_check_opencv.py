import cv2
import numpy as np

def process_image(image_path, action, parameters={}):
    # Load image
    img = cv2.imread(image_path)

    if action == "to_grayscale":
        # Convert to grayscale
        img_processed = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    elif action == "change_brightness":
        # Adjust brightness
        brightness_value = parameters.get("brightness_value", 0)
        brightness_matrix = np.ones(img.shape, dtype=np.uint8) * abs(brightness_value)
        img_processed = cv2.add(img, brightness_matrix) if brightness_value > 0 else cv2.subtract(img, brightness_matrix)
    elif action == "equalize_histogram":
        # Histogram equalization on specified color space
        color_space = parameters.get("color_space", "hsv").lower()
        if color_space == "hsv":
            img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
            h, s, v = cv2.split(img_hsv)
            v_equalized = cv2.equalizeHist(v)
            img_processed = cv2.cvtColor(cv2.merge((h, s, v_equalized)), cv2.COLOR_HSV2BGR)
        elif color_space == "hsl":
            img_hsl = cv2.cvtColor(img, cv2.COLOR_BGR2HLS)  # OpenCV uses HSL as HLS
            h, l, s = cv2.split(img_hsl)
            l_equalized = cv2.equalizeHist(l)
            img_processed = cv2.cvtColor(cv2.merge((h, l_equalized, s)), cv2.COLOR_HLS2BGR)
    elif action == "threshold":
        # Thresholding
        threshold_value = parameters.get("threshold_value", 127)
        color_space = parameters.get("color_space", "gray").lower()
        if color_space == "gray":
            gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            _, img_processed = cv2.threshold(gray_img, threshold_value, 255, cv2.THRESH_BINARY)
        elif color_space in ["hsv", "hsl"]:
            if color_space == "hsv":
                img_cs = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
            else:  # HSL
                img_cs = cv2.cvtColor(img, cv2.COLOR_BGR2HLS)
            c, _, _ = cv2.split(img_cs)
            _, img_processed = cv2.threshold(c, threshold_value, 255, cv2.THRESH_BINARY)
    else:
        return None  # Unsupported action

    # Construct save path based on action
    save_path = f"./{action}_{parameters.get('suffix', '')}_{image_path.split('/')[-1]}"
    if img_processed.ndim == 2:
        # For grayscale or thresholded images, ensure correct color mapping on save
        cv2.imwrite(save_path, img_processed)
    else:
        cv2.imwrite(save_path, img_processed)

def calculate_image_difference(image_path1, image_path2):
    img1 = cv2.imread(image_path1)
    img2 = cv2.imread(image_path2)
    diff = cv2.absdiff(img1, img2)
    mean_diff = np.mean(diff)
    max_diff = np.max(diff)
    std_diff = np.std(diff)
    return mean_diff, max_diff, std_diff
