> Open LookbackOptionPricer.xlsm
> Open Visual Basic and go to Module3
> Direct paths need to be changed :
- During .dll declaration, the file is in LookbackOption/Debug
- in pricer macro, ChDir is the current path
- in openCSVfile, you need to find where the .dll create results.csv (in our case it was in Documents)
> Save it
> Now, pricer must work correctly.