touch tests//.timeout
CMD="valgrind --leak-check=full /home/isaac/NetBeansProjects/Language5/./dist/JOIN/GNU-Linux/JOIN  -o tests/output/10bigrams_10bigrams.bgr ../Books/10bigrams.bgr ../Books/10bigrams.bgr 1> tests//.out6 2>&1"
eval $CMD
rm tests//.timeout
