trackpoint-control
===================

Management for ThinkPad TrackPoint settings

# Functionality
- Control all available trackpoint parameters in sysfs
- Load/save settings
- Reset values to default
- trackpoint-control-helper changes settings as root user

# Requirements
- C compiler (i.e. gcc)
- Qt 5.x
- python3

# Installation
    git clone https://github.com/jmechnich/trackpoint-control.git
    
    # compile and install
    cd trackpoint-control
    make
    sudo make install
    
    # run program
    trackpoint-control

# Screenshots

![](https://raw.github.com/jmechnich/trackpoint-control/master/screens/screen.png)
