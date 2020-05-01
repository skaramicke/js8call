parameter (NCOSTAS=2)                 !Which JS8 Costas Arrays to use (1=original, 2=three symmetrical costas)

parameter (NSPS=3840, NTXDUR=28, NDOWNSPS=32, NDD=90,  JZ=32)  !  25 Hz  3.125 baud  8 wpm -28.0dB (1.0Eb/N0) 25.28s

parameter (AZ=12000.0/(1.0*NSPS)*0.64d0) !Dedupe overlap in Hz
parameter (ASTART=0.5)                   !Start delay in seconds
parameter (ASYNCMIN=1.5)                 !Minimum Sync

parameter (KK=87)                     !Information bits (75 + CRC12)
parameter (ND=58)                     !Data symbols
parameter (NS=21)                     !Sync symbols (3 @ Costas 7x7)
parameter (NN=NS+ND)                  !Total channel symbols (79)
parameter (NZ=NSPS*NN)                !Samples in full 15 s waveform (151,680)
parameter (NMAX=NTXDUR*12000)         !Samples in iwave (180,000)
parameter (NFFT1=2*NSPS, NH1=NFFT1/2) !Length of FFTs for symbol spectra
parameter (NSTEP=NSPS/4)              !Rough time-sync step size
parameter (NHSYM=NMAX/NSTEP-3)        !Number of symbol spectra (1/4-sym steps)
parameter (NDOWN=NSPS/NDOWNSPS)       !Downsample factor to 32 samples per symbol
parameter (NQSYMBOL=NDOWNSPS/4)       !Downsample factor of a quarter symbol
