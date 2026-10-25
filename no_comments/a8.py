import cv2

clf = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
img = cv2.imread("image.jpg")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

faces = clf.detectMultiScale(gray, 1.1, 5)
print(f"Found {len(faces)} faces!")

for (x, y, w, h) in faces:
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)

cv2.imshow("Faces", img)
cv2.waitKey(0)
