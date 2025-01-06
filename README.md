Document: https://docs.google.com/document/d/1WZRMCZCcDeq7lePxCiqcADXola2YHmroq0DYWtivh3I/edit?usp=sharing (see this for the most updated version :))
# Overall workflow
![EasyProj ReadMe](https://github.com/user-attachments/assets/20e82a36-c0e2-403d-b620-a52259b6f70b)
# Modes
- **Multiplex Mode** follow such structure: <br>
Image 1 -> Dark -> Image 2 -> Dark -> …. -> Image N -> Dark
Example: 2-image multiplexing <br>
![Picture2](https://github.com/user-attachments/assets/b09854ed-6962-4757-b50c-6dc4a5d28f1a)<br>
Repeats this process infinitely <br>
- **Sequence Mode** follow such structure <br>
Image 1 -> Dark -> Image 1 -> Dark -> ….. -> Image 1 nth time -> Dark -> Image 2 -> Dark -> Image 2 -> Dark -> …. -> Image 2 nth time -> Dark -> Image 3 -> Dark ……… <br>
Each image is repeated N times before next image <br>
Repeats this process infinitely <br>
Example: 2-image 2-repetition sequence (set Repetition to 2, see first image) <br>
![Picture1](https://github.com/user-attachments/assets/96b8a5c1-478d-4863-b902-fc08db69b3af) <br>
# About timing: <br>
ON: how long do you want the image to be displayed? <br>
OFF: how long do you want the dark time to be? <br>
What is the largest common denominator for ON & OFF timing? <br>
An example: <br>
I want ON for 20000 microseconds <br>
I want OFF for 10000 microseconds <br>
Set PictureTime (see on first image) to be 10000 (unit is microseconds) <br>
Enter 2 for ON (2 * 10000) <br>
Enter 1 for OFF (1 * 10000) <br>
# Additional Notes
## Multiplex Mode
Make sure values sum <= 16 <br>
Otherwise increase PictureTime or select less images <br>
![EasyProj ReadMe (4)](https://github.com/user-attachments/assets/b009ad02-e022-43a7-9cb2-bc33759716d7) <br>
## If stopped projection
- If want to continue the same projection: Set -> Projection <br>
- If want to change another projection with different images: Load -> Set -> Projection <br>
- If there is any strange issue: quit and restart please


