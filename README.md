# Modelling_Seminar_SoSe24
> Topic 6: Domain Decomposition Methods under Constraints in CFD Simulations

## This was a dump location for our Modelling Seminar 2025. The working stuff is in BACKUP, just download the latest one and if there are problems use the metis version provided. Refer to the provided PDFs for a walkthrough. Reach out only if something noteworthy comes up viz. if it has potential for impact, visibility, or value.



<PART OF OLD README>
<details>
<summary>
  A simple guide to get METIS working on your linux machine :)
</summary>

## Steps to install METIS:
1. Download the metis-5.1.0.tar.gz in your local directory.
2. Open the terminal and change your current directory to the directory where you downloaded the metis-5.1.0.tar.gz
3. Just copy-paste and run the following commands in your terminal in the given order to make your life a bit simpler.
```
tar -xvzf metis-5.1.0.tar.gz
```
4. We have to edit the file 'include/metis.h' and specify the width (64 bits) of the elementary data type used in METIS. This is controled by the IDXTYPEWIDTH constant.
```
vim metis-5.1.0/include/metis.h
```
5. This will open the header file in terminal. Edit the value infront *#define IDXTYPEWIDTH* to 64 (Line number 33).
6. Now you'll have to save the file and close the vim by pressing 'Esc' then type ':wq' and then press 'Enter'. Then execute next commands:
```
cd metis-5.1.0/
```
```
sudo make -j $nproc
```
```
sudo make install -j $nproc
```

or the NOOB's way
```
sudo apt-get install libmetis5 libmetis-dev metis
```~

Congratulations!
</details>

