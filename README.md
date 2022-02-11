# Soundpp

![](CODE/soundpp/soundpp-prototype/img/logo_groß.png)


Music player implemented in C++ and Qt.

The source code is stored in:<br />
/soundpp/CODE/soundpp/soundpp-prototype/

## Compiling
### Ubuntu 

-- Our installation process for ubuntu in Virtual Box :  
````bash
udo apt-get update && sudo apt-get upgrade
````

After installing guest and additions restart vm :
````bash
sudo reboot
````

Install qtcreator:
````bash
sudo apt install gcc g++ make qtcreator qt5-default
````

Install qt MultiMedia:
````bash
 sudo apt-get install qtmultimedia5-dev
````

Install Multimedia Plugins:
````bash
sudo apt-get install libqt5multimedia5-plugins
````

Install the LibTag library (its for getting meta-data from musicfiles):
````bash
sudo apt-get install libtag1-dev
````

Install GStreamer for Ubuntu (for more audioformats like aiff):
````bash
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
````

Install git (for cloning project):
````bash
sudo apt install git
````

Install git-lfs (for some example songs):
````bash
sudo apt install git-lfs
````

Optional install sqllite3 (it works without extra installtion):
````bash
sudo apt install sqlite3
````

Clone the project (Finally!):
````bash
git clone https://github.com/b1t00/soundpp.git
````

Maybe you will need the Github Token as password, then write us

open pro file in the qt creator, compile, drop your favorite songs in mp3 and wav format and listen

These settings worked for us, please tell us, if something dont work proper
We tested it most of the time in windows 10.

### Windows 

you have to use the MinGW64 compiler in QTCreator, because of the TagLib dll files. Maybe you have to compile the tagLib dll files for you self
but there we put out dlls in the project folder
otherwise it should work 

## Projekt Discription

Soundpp is a desktop musikplayer for your offline musiklibrary.

#### Functionalities and behaviour:

**Load songfiles:**<br />
use the open... action in the menubar file->open... or 
Drag and Drop musikfiles (we working on dropping folders).<br />
Accapted formats are mp3, wav, aiff. Maybe more are possible. It also depends on installed audio-codes (we suspecting).<br />
(we work to add more file formats, by substitute our library of the QTMusikplayer-class)

*BUG:*<br />
Not every mp3 file works, there are also different formats for mp3.

*Note:*<br />
Wav files have no meta data header for artist, album etc.. so you will see Unknown Artist,but you can allways editing the song meta data.

**Play songs:**<br />
You can double click every song to play directly.<br />
You can add songs to the queue (next song or last song in queue list).<br />
If you double click an artist or an album, 
the first song of the artist or album is playing directly, the other songs will be add to you queue list.<br />
You can also add all songs from an artist or album to the queue list (context menu).

**Queue list and history:**
<br />
You have a queue list, where you can add songs for the listening queue.<br />
You can also remove the songs from the queue list.<br />
You can go to the history and play songs from it.<br />
If you push the <- back button in the player controls before 1 sec of the current song is played (push twice), you will go throught your history.
But after listening to the song in the history it continous with the queue list.<br />

**Searching and sorting:**
<br />
You can search for song titles, artists or albums.<br />
You can order songs by clicking on table headers, 
for example the playcount sorting shows your favorite songs.

**View:**<br />
You can switch between a bright or dark mode in the menu bar -> view -> dark mode. <br />
You can hide or show columns of the song table in the menu bar, or the context menu (right click on songtable header)<br />
You can rezise tables (in some settings it looks a bit buggy, we working on the right settings for that).<br />

#### Not finished:<br />
The Playlists are not finished yet. You can not add songs to playlists.
#### Future ideas:<br />
We want to add the categories genre and labels. And try to get the meta data from discogs.<br />
We want to substitute the musikplayer-class for a musikplayer with more supported formats like Alac, Flac etc. <br />
We want to add some pitch and soundeffect features. <br />
We also want to clean up the source code and want to use more connections in Qt to outsource code from the Mainwindow.cpp (ui->). 
<br />
<br />

<br />
<br />
Have fun with soundpp and listen to some nice music :) 

Please tell us any suggestions or improvements. In coding or usability.

Simon Dannemann 5017489 & Tobi Schmitt 5052509