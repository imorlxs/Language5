touch tests//.timeout
CMD="valgrind --leak-check=full /home/isaac/NetBeansProjects/Language5/./dist/JOIN/GNU-Linux/JOIN  -o tests/output/spanish.bgr ../Books/BodasdeSangre_FedericoGarciaLorca.bgr ../Books/quijote.bgr 1> tests//.out14 2>&1"
eval $CMD
rm tests//.timeout
