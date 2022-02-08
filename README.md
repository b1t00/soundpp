# soundpp

![](CODE/soundpp/soundpp-prototype/img/logo_groß.png)


Music player implemented in c++ and qt.

the source code is stored in: /soundpp/CODE/soundpp/soundpp-prototype/

Requirements:

-- Ubuntu

Our installation process for ubuntu in Virtual Box: 
- terminal: sudo apt-get update && sudo apt-get upgrade

Installing guest additions (just for vm propose)
- terminal: sudo reboot //(to run guest additions)

Install qtcreator 
- terminal: sudo apt install gcc g++ make qtcreator qt5-default

Install qt MultiMedia:
- terminal: sudo apt-get install qtmultimedia5-dev

Install Multimedia Plugins:
- terminal: sudo apt-get install libqt5multimedia5-plugins

Install the LibTag library (its for getting meta-data from musicfiles)
- terminal: sudo apt-get install libtag1-dev

Install GStreamer for Ubuntu (for more audioformats like aiff)
- terminal: sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

Install git (for cloning project)
- terminal: sudo apt install git

Install git-lfs (for some example songs)
- terminal: sudo apt install git-lfs

Optional install sqllite3 (it works without extra installtion)
- terminal: sudo apt install sqlite3

Clone the project (Finally!)
- terminal: https://github.com/b1t00/soundpp.git
Maybe you will need the Github Token as password:
TODO:: ******
(please be responsible with it)

open pro file in the qt creator, compile, drop your favorite songs in mp3 and wav format and listen

These settings worked for us, please tell us, if something dont work proper
We tested it most of the time in windows 10.


in windows:
you have to use the MinGW64 compiler in QTCreator, because of the TagLib dll files. Maybe you have to compile the tagLib dll files for you self
but there we put out dlls in the project folder
otherwise it should work 


//----------------------------------------- Projekt-Discription ------------------------------------------------------------------------//

Soundpp is a desktop musikplayer for your offline musiklibrary

functionalities and behaviour:

-- loading your songfiles
use the open... action in the menubar file->open... or 
Drag and Drop musikfiles (we working on dropping folders)
accapted formats are mp3, wav, aiff. Maybe more are possible. It also depends on installed audio-codes (we suspecting).
(we work to add more file formats, by substitute our library of the QTMusikplayer-class)
-BUG:: not every mp3 file works, there are also different formats for mp3
-Notice:: wav files have no meta data header for artist, album etc.. so you will see Unknown Artist,but you can allways editing the song meta data

-- Playing songs
you can double click every song to play directly
you can add songs to the queue (next song or last song in queue list)
if you double click an artist or an album, 
the first song of the artist or album is playing directly, the other songs will be add to you queue list
you can also add all songs from an artist or album to the queue list (context menu)

-- Queue List and History
You have a queue list, where you can add songs for the listening queue
You can also remove the songs from the queue list
You can switch to the history. 
If you push the <- back button in the player controls before 1 sec of the current song is played (push twice), you can go throught you history
After listening to the song in the history it continous with the queue list

-- Searching and Sorting
You can search for song titles, artists or albums
you can order songs by clicking on table headers, 
for example the playcount sorting shows your favorite songs or adding date for your newest songs

-- View
you can switch between a bright or dark mode in the menu bar -> view -> dark mode
you can hide or show columns of the song table in the menu bar, or the context menu (right click on songtable header)
you can rezise tables (in some settings it looks a bit buggy, we working on the right settings for that)


Have fun with soundpp and listen to some nice music :) 

Please tell us any suggestions or improvements. In coding or usability.

Simon 5017489 & Tobi 

In the future:
we have a lot of ideas 
