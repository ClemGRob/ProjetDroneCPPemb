# ProjetDroneCPPemb

welcome to the V1.0 release of our steganography project.
we have to hide a position inside of a picture and send it with mqtt to the base.

# requierement
tested on ubuntu 20.04 and qt 5.12

# build
## with qt creator
open qtcreator
open folders "drone" and "base" and build it (release mode)
## prompt
open a first prompt, we will call it "drone prompt" 
cd drone
make -j20

open a second prompt, we will call it "base prompt" 
cd base
make -j20



# run
## with qt creator
click on base run button and after drone run button
## prompt
we start with base : 
### base prompt
cd ../build-base-Desktop-Release
./base

### drone prompt
cd ../build-drone-Desktop-Release
./drone

