import face_recognition
import cv2
import numpy as np

def setup_facerec():
    global known_face_names, known_face_encodings
    known_face_names = ["morris", "obama", "biden"]
    known_face_encodings = [np.load("encodings/%s.npy" % name) for name in known_face_names]


def frame_detect(frame, draw=False):
    scale = 5

    # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
    rgb_frame = frame[:, :, ::-1]
    rgb_frame = cv2.resize(rgb_frame, (0, 0), fx=1./scale, fy=1./scale)

    # Find all the faces and face enqcodings in the frame of video
    face_locations = face_recognition.face_locations(rgb_frame)
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

    results = []

    # Loop through each face in this frame of video
    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        top *= scale
        right *= scale
        bottom *= scale
        left *= scale

        # See if the face is a match for the known face(s)
        face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
        name = "unknown"
        idx = 0
        min_face_distance = 1.0
        for i, face_distance in enumerate(face_distances):
            if face_distance < min_face_distance:
                min_face_distance = face_distance
                idx = i
        if min_face_distance < 0.40:
            name = known_face_names[idx]
        conf = (1-min_face_distance)*100

        results.append({
            "name" : name,
            "top" : top,
            "bottom" : bottom,
            "left" : left,
            "right" : right,
            "conf" : conf
        })

        # Draw a box around the face
        if draw:
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
            cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
            font = cv2.FONT_HERSHEY_DUPLEX
            cv2.putText(frame, "%s:%.2f" % (name, conf), (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)

    return results


if __name__ == "__main__":
    video_capture = cv2.VideoCapture(0)

    setup_facerec()

    while True:
        # Grab a single frame of video
        ret, frame = video_capture.read()

        results = frame_detect(frame, draw=True)

        # Display the resulting image
        cv2.imshow('Video', frame)

        # Hit 'q' on the keyboard to quit!
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release handle to the webcam
    video_capture.release()
    cv2.destroyAllWindows()
