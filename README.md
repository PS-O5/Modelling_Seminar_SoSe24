# Modelling_Seminar_SoSe24
Topic 6: Domain Decomposition Methods under Constraints in CFD Simulations

> [!NOTE]
> A simple guide to let METIS working on your linux machine :)

## Steps to install METIS:
Download the metis-5.1.0.tar.gz in your local directory.
Open the terminal and change your current directory to the directory where you downloaded the metis-5.1.0.tar.gz
Just copy-paste and run the following commands in your terminal in the given order to make your life a bit simpler.
```
tar -xvzf metis-5.1.0.tar.gz
```
Edit the file include/metis.h and specify the width (64 bits) of the elementary data type used in METIS. This is controled by the IDXTYPEWIDTH constant. Then do the following
```
cd metis-5.1.0/
```
```
sudo make -j $nproc
```
```
sudo make install -j $nproc
```

Congratulations!
