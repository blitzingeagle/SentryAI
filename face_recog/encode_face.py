import face_recognition
import numpy as np

filename = "biden"

image = face_recognition.load_image_file("%s.jpg" % filename)
face_encoding = face_recognition.face_encodings(image)[0]

print(face_recognition)

np.save("encodings/%s.npy" % filename, face_encoding)