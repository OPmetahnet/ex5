/******************
Name: Oz Pinto
ID: 212320733
Assignment: 5
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song* songs;
    int songsNum;
} Playlist;

//some recommendations for functions, you may implement however you want

//gets a string input from the user and inserts it for the given string type argument
char* getStringInput() {
    char inputChar, * stringToGet = NULL;
    int size = 1;//init to 1 for the purpose of ending with null char \0

    scanf(" %c", &inputChar);
    stringToGet = (char*)malloc((++size) * sizeof(char));
    if(stringToGet == NULL) {
        printf("malloc failed\n");
        exit(1);
    }
    stringToGet[size - 2] = inputChar;
    stringToGet[size - 1] = '\0';

    /*
     keep getting characters from the buffer,
     place a null char at the end to signify the end of the string
    */
    while(scanf("%c", &inputChar) && inputChar != '\n' && inputChar != '\r') {
        stringToGet = realloc(stringToGet, (++size) * sizeof(char));
        if(stringToGet == NULL) {
            printf("realloc failed\n");
            exit(1);
        }
        stringToGet[size - 2] = inputChar;
        stringToGet[size - 1] = '\0';
    }

    return stringToGet;
}

//adds a song to the given playlist
Playlist addSong(Playlist playlist, char* songTitle, char* songArtist, char* songLyrics ,int songYear) {
    int newSize = playlist.songsNum + 1;

    //allocate memory for the song
    playlist.songs = (Song*)realloc(playlist.songs, (newSize) * sizeof(Song));
    if(playlist.songs == NULL) {
        printf("realloc failed\n");
        exit(1);
    }

    //update song details
    playlist.songs[newSize - 1].title = strdup(songTitle);
    playlist.songs[newSize - 1].artist = strdup(songArtist);
    playlist.songs[newSize - 1].lyrics = songLyrics;
    playlist.songs[newSize - 1].year = songYear;
    playlist.songs[newSize - 1].streams = 0;
    playlist.songsNum++;

    return playlist;
}

void deleteSong() {

    printf("Song deleted successfully.\n");
}



void playSong() {
    
}


//frees a song from the memory
void freeSong(Song* song) {
    if(song != NULL) {
        free(song->title);
        song->title = NULL;
        free(song->artist);
        song->artist = NULL;
        free(song->lyrics);
        song->lyrics = NULL;
    }
}

//add a playlist
Playlist* addPlaylist(Playlist* account, int size, char* name) {
    account = (Playlist*)realloc(account, (++size) * sizeof(Playlist));
    if(account == NULL) {
        printf("realloc failed\n");
        exit(1);
    }

    //update the playlist's name
    account[size - 1].name = strdup(name);
    account[size - 1].songs = NULL;
    account[size - 1].songsNum = 0;

    return account;
}

//frees a playlist from the memory
void freePlaylist(Playlist* playlist) {
    
}

//prints main menu
void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");   
}

//prints the list of existing playlists
void printPlaylistsSelectionList(Playlist* account, int size) {
    for(int i = 0; i <= size; i++) {
        if(i == size) {
            printf("%d. Back to main menu\n", i + 1);
            return;
        }
        printf("%d. %s\n",  i + 1 ,account[i].name);
    }
}

//prints the list of songs in the given playlist
void printSongsList(Playlist playlist) {
    for(int i = 0; i < playlist.songsNum; i++) {
        printf("%d. Title: %s\n"
                      "   Artist: %s\n"
                      "   Released: %d\n"
                      "   Streams: %d\n",
        i + 1, playlist.songs[i].title, playlist.songs[i].artist, playlist.songs[i].year, playlist.songs[i].streams);
    }
}

//prints a specific playlist's actions menu
void printPlaylistActionsMenu() {
    printf("\t1. Show Playlist\n\t2. Add Song \n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}

void sortPlaylist() {
    
    printf("sorted\n");
}

int main() {
    int mainMenuChoice = -1;

    Playlist* account = NULL;
    int size = 0;

    //menu
    do {
        printPlaylistsMenu();

        if(scanf("%d", &mainMenuChoice)) {
            switch(mainMenuChoice) {
                //watch playlist
                case 1: {
                    int playlistMenuChoice = -1;

                    do {
                        //print menu and get a choice input
                        printPlaylistsSelectionList(account, size);
                        scanf("%d", &playlistMenuChoice);

                        //make sure that the number fits in the right range
                        while(playlistMenuChoice < 1 || playlistMenuChoice > size + 1) {
                            printf("Invalid option\n");
                            printPlaylistsSelectionList(account, size);
                            scanf("%d", &playlistMenuChoice);
                        }

                        //if last option(exit) has been chosen go back to the previous menu
                        if(playlistMenuChoice == size + 1) {
                            break;
                        }

                        int playlistActionsMenuChoice = -1;
                        int playlistNameDisplayFlag = 0;

                        //actions menu loop
                        do {
                            //if playlist name hasn't been displayed yet in this menu session/iteration, display it
                            if(playlistNameDisplayFlag == 0) {
                                printf("playlist %s\n", account[playlistMenuChoice - 1].name);
                                playlistNameDisplayFlag = 1;
                            }

                            //open relevant playlist actions menu and get a choice for it
                            printPlaylistActionsMenu(account[playlistMenuChoice - 1]);
                            scanf("%d", &playlistActionsMenuChoice);

                            switch(playlistActionsMenuChoice) {
                                //show playlist songs to play
                                case 1: {
                                    int songToPlay = -1;

                                    //get a song to play
                                    printf("choose a song to play, or 0 to quit:\n");
                                    printSongsList(account[playlistMenuChoice - 1]);

                                    scanf("%d", &songToPlay);

                                    //check if in range, otherwise go back
                                    

                                    break;
                                }
                                //add a song to the playlist
                                case 2: {
                                    char* songTitle = NULL, * songArtist = NULL, * songLyrics = NULL;
                                    int yearOfRelease;

                                    //get the song's title
                                    printf("Enter song's details\nTitle:\n");
                                    songTitle = getStringInput();

                                    //get the song's artist
                                    printf("Artist:\n");
                                    songArtist = getStringInput();

                                    //get the year of release
                                    printf("Year of release:\n");
                                    scanf("%d", &yearOfRelease);

                                    //get the song's lyrics
                                    printf("Lyrics:\n");
                                    songLyrics = getStringInput();

                                    //add the song to the playlist
                                    account[playlistMenuChoice - 1] = addSong(account[playlistMenuChoice - 1], songTitle, songArtist, songLyrics,
                                            yearOfRelease);

                                    //free the placeholders from the memory
                                    free(songTitle);
                                    free(songArtist);
                                    free(songLyrics);

                                    break;
                                }
                                //delete a song
                                case 3: {
                                    break;
                                }
                                //sort playlist by a chosen parameter
                                case 4: {
                                    break;
                                }
                                //play
                                case 5: {
                                    break;
                                }
                                //exit to previous menu
                                case 6: {
                                    break;
                                }
                                //nonexistent option
                                default: {
                                    printf("Invalid option\n");
                                    break;
                                }
                            }
                        }
                        while(playlistActionsMenuChoice != 6);
                    }
                    while(playlistMenuChoice != size + 1);

                    break;
                }
                //add a new playlist
                case 2: {
                    char* playlistName = NULL;

                    //get name for the playlist
                    printf("Enter playlist's name:\n");
                    playlistName = getStringInput();

                    //create the new playlist and add it
                    account = addPlaylist(account, size, playlistName);
                    size++;

                    //free the allocated memory for the name placeholder
                    free(playlistName);

                    break;
                }
                //remove an existing playlist
                case 3: {


                    break;
                }
                //exit
                case 4: {
                    //free all playlists/songs data and clean buffer


                    printf("Goodbye!\n");
                    break;
                }
                default: {
                    printf("Invalid option\n");
                    break;
                }
            }
        }
        else
        {
            scanf("%*s");
        }
    }
    while (mainMenuChoice != 4);
}
