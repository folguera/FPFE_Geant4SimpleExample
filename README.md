# FPFE_Geant4SimpleExample

###  Load environment
```
source /opt/root/root-6.24.06_install/bin/thisroot.sh
source /opt/geant4/geant4-v10.07.p03_install/bin/geant4.sh
```

###  Compile
```
cd exampleB4d_build/
cmake -DGeant4_DIR=opt/geant4/geant4-v10.07.p03_install/lib/Geant4-10.7.3/ ../
make -j 4 exampleB4d
./exampleB4d -m macro.mac
```
