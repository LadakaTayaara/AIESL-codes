"""
Problem: Face Detection (Assignment 8)
Technique: Computer Vision - Viola-Jones Algorithm using Haar Feature-based Cascade Classifier

Key Concepts:
1. Haar-like Features: Rectangular digital image features used to rapidly evaluate light/dark
   contrasts (e.g. eye region is darker than upper cheeks, bridge of nose is brighter).
2. Integral Image: Allows constant-time O(1) calculation of rectangular pixel area sums.
3. Adaboost: Selects the most discriminative features out of over 160,000+ possibilities.
4. Cascade of Classifiers: Applies simple filters first; non-face regions are rejected
   almost immediately, allocating computational power only to face-like candidate regions.
"""

import cv2

# 1. Load the pre-trained Haar Cascade XML model for frontal face detection
# OpenCV provides this pre-trained model for detecting frontal human faces
clf = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")

# Fallback: if not using cv2.data path, check local folder
if clf.empty():
    clf = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

# 2. Read the input image from disk
img = cv2.imread("image.jpg")

if img is None:
    print("Error: Could not load image.jpg. Ensure 'image.jpg' exists in the directory.")
else:
    # 3. Convert image from BGR color space to Grayscale
    # Haar Cascades operate on single-channel grayscale intensity images
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 4. Detect faces in the grayscale image
    # - scaleFactor=1.1: Specifies how much the image size is reduced at each image scale (10% pyramid reduction)
    # - minNeighbors=5: How many neighboring candidate rectangles must overlap to retain a detection (filters false positives)
    faces = clf.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)

    print(f"Found {len(faces)} face(s)!")

    # 5. Draw green bounding boxes around all detected faces
    # Each face is represented as a bounding rectangle: (x, y, width, height)
    for (x, y, w, h) in faces:
        # cv2.rectangle(image, top_left_corner, bottom_right_corner, color_BGR, thickness)
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)

    # 6. Display the output image in a window
    cv2.imshow("Detected Faces", img)

    # Wait indefinitely until any keyboard key is pressed, then close window
    cv2.waitKey(0)
    cv2.destroyAllWindows()
