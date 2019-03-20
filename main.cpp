#include <windows.h>
#include <string>
#include <list> 
#include <iterator> 
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <strsafe.h>
using namespace std;

string getRootPath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

char tolower(char in) {
  if(in <= 'Z' && in >= 'A')
    return in - ('Z' - 'z');
  return in;
}

string toLowerStr(string input){
	for(int i=0; i<input.length(); i++){
		input[i] = tolower(input[i]);
	}
	return input;
}

void blink(char c1, char c2, int times){
	string instruction1 = "color ";
	instruction1 += c1; instruction1 += c2;
	string instruction2 = "color " + c2 + c1;
	instruction2 += c2; instruction2 += c1;
	for(int i=0; i<times; i++){
		system(instruction1.c_str());
		system(instruction2.c_str());
	}
}

void color(char c1, char c2){
	string instruction = "color ";
	instruction += c1; instruction += c2;
	system(instruction.c_str());
}

void wait(int seconds){
	string instruction = "timeout /t " + seconds;
	system(instruction.c_str());
}

void clear(){
	system("cls");
}

void pause(){
	system("pause");
}

int getNumElements(string elements){
    int counter = 0;
    for(int i=0; i<elements.length(); i++){
        if(elements[i] == '.'){
            counter++;
        }
    }
    return counter - 1;
}

string getExtensionsArray(string extensions, int pos){
    int counter = getNumElements(extensions);

    string extensionsList[counter];
    int startSubStr = 0;
    int endSubStr = 0;
    int counterList = 0;

    for(int i=0; i<extensions.length(); i++){
        if(i > 0){i--;}
        if(extensions[i] == '.'){
            i++;
            startSubStr = i;
            while(true){
                if(extensions[i] == '.'){
                    endSubStr = i-startSubStr;
                   break;
                }
                //   break;
                i++;
            }
            extensionsList[counterList] = extensions.substr(startSubStr, endSubStr);
            counterList++;
            startSubStr = 0;
            endSubStr = 0;
        }
    }
    return extensionsList[pos];
}

string createDestinationPath(string backupPath, string backupFolderName, string categoryFolder, boolean createIt){
	//Define BackupPath depending on backup folder is speciied or not.
	//								 Or if it has '\' at the end.
	string destinationPath;
	string instruction;
	
    if(backupPath != "aqui"){	
	    if(backupPath[backupPath.length() - 1] == '/' || backupPath[backupPath.length() - 1] == '\u005C'){
	    	instruction =  "md \u0022" + backupPath + backupFolderName + '\u005C' + categoryFolder + "\u005C\u0022";
		    destinationPath = instruction.substr(4); //Clones the Destination Path
		} else {		
	    	instruction =  "md \u0022" + backupPath + '\u005C' + backupFolderName + '\u005C' + categoryFolder + "\u005C\u0022";
		    destinationPath = instruction.substr(4); //Clones the Destination Path
		}
	} else if(backupPath == "aqui"){
	    	instruction =  "md \u0022" + backupPath + backupFolderName + '\u005C' + categoryFolder + "\u005C\u0022";
		    destinationPath = instruction.substr(4); //Clones the Destination Path
	}
	
	if(createIt){ // Asks for creating the folder or returning path only
		system(instruction.c_str());
		instruction.clear();	
	} else {
		destinationPath = destinationPath.substr(0,destinationPath.length()-2) + '\u0022';
	}
	return destinationPath;
}

void printMenu(){
	cout << "\n  Que tipos de archivo deseas extraer?:\n";
    cout << "    1: Personalizado (Tendras que ingresar las extensiones)\n";
    cout << "    2: Documentos (.docx /.doc /.pdf /.pptx /.ppt /.xlsx /.xls /.txt /.rtf /.odt)\n";
    cout << "    3: Audio (.mp3 /.m4a /.flac /.wav /.wma /.aac /.amr /.ogg)\n";
    cout << "    4: Imagen (.jpg /.jpeg /.png /.gif / .psd / .WebP /.bmp /.tiff /.raw)\n";
    cout << "    5: Video (.mp4 /.3gp /.avi /.wmv /.gif /.mov /.flv /.mpg /.mpeg /.WebM)\n";		
    cout << "    0: SALIR\n";
}

void printInstructions(){
	cout << "\n  Instrucciones:\n";
    cout << "    1) Coloca este archivo en el directorio a BUSCAR.\n";
    cout << "    2) Ejecutalo y personaliza tus OPCIONES.\n";
    cout << "    3) Ingresa la RUTA de EXTRACCION.\n";
    cout << "    4) Listo!.\n";
}

void printLogo(){
	cout << "\n          _____ __                         __";
	cout << "\n         / ___// /________________ _____  / /";
	cout << "\n         \u005C__ \u005C/ //_/ ___/ ___/ __ `/ __ \u005C/ / ";	
	cout << "\n        ___/ / ,< / /  / /  / /_/ / /_/ /_/  ";	
	cout << "\n       /____/_/|_/_/  /_/   \u005C__,_/ .___(_)  ";	
	cout << "\n                                /_/        \n";
	cout << "                                 Version 1.0\n";
	cout << "                               By Shafool\n";
	cout << "                            GitHub.com/Shafool\n";
}

void printSelected(string optionsSelected){
	cout << "      Seleccionados: ";
	if(optionsSelected.length() == 0){
	 	cout << "Ninguno"; 
	}else{
		for(int i=0; i<optionsSelected.length(); i++){
			if(i != 0) cout << ", ";
			switch(optionsSelected[i]){
				case '1':
					cout << "Personalizado";
				break;
				case '2':
					cout << "Documentos";
				break;
				case '3':
					cout << "Audio";
				break;
				case '4':
					cout << "Imagen";
				break;
				case '5':
					cout << "Video";
				break;
			}
		}
	}
}

void extract(char selection, string root, string backupPath, string backupFolderName, string optionsSelected, string hereCondition){	
	string categoryFolder;
	string destinationPath;
	string instruction;
	
	if(selection == '1'){ //Personalized    				
		// SPACEBAR finish the input
	    // ENTER stores the new extension
	    // BACKSPACE clears the input
	
		/* Creating the extensions array*/
	    char keyPressed;
	    int counter = 1;
	    
	    string newExtension = "";
	    string planeTextExtensions = "";
	    
	    list <string> extensionsList;
	    list <string> :: iterator it; 
		
	    while(true){
	    	printLogo();
	    	cout << "\n   1) OPCIONES SELECCIONADAS\n";
	    	printSelected(optionsSelected); cout << '\n';
	    	cout << "\n   2) SE EXTRAERA EN:\n";
			cout << "      " << createDestinationPath(backupPath, backupFolderName, "\b", false) << '\n';
	
	    	cout << "\n   3) Personaliza tus EXTENSIONES (Presiona ESPACIO para terminar y BORRAR para corregir)\n";
	    	cout << "      Extensiones ingresadas: ";
			if(extensionsList.empty() == 1){
   		 		cout << "Ninguno";
			} else {
				list <string> :: iterator it; 
  	    		for(it = extensionsList.begin(); it != extensionsList.end(); ++it){
  	    			cout << *it << ' '; 
				}	
			}
			cout << '\n';
			
	        cout << "Escribe tu extension #" << counter << " >> .";
	        while(true){
	            keyPressed=getch();
	            if((int)keyPressed == 13 || (int)keyPressed == 32){ //When Enter or Space pressed, finish
	                break;
	            } else if ((int)keyPressed == 8){ //When Backspace pressed and list is not empty
	                newExtension.clear();
	                if(extensionsList.empty() != 1){
	                	extensionsList.pop_back();
	        			counter--;
					}
					
					system("cls");
					
					printLogo();
	                cout << "\n   1) OPCIONES SELECCIONADAS\n";
			    	printSelected(optionsSelected); cout << '\n';
			    	cout << "\n   2) SE EXTRAERA EN:\n";
					cout << "      " << createDestinationPath(backupPath, backupFolderName, "\b", false) << '\n';
			
			    	cout << "\n   3) Personaliza tus EXTENSIONES (Presiona ESPACIO para terminar y BORRAR para corregir)\n";
			    	cout << "      Extensiones ingresadas: ";
					if(extensionsList.empty() == 1){
		   		 		cout << "Ninguno";
					} else {
						list <string> :: iterator it; 
		  	    		for(it = extensionsList.begin(); it != extensionsList.end(); ++it){
		  	    			cout << *it << ' '; 
						}	
					}
					cout << '\n';
					cout << "Escribe tu extension #" << counter << " >> .";	
	            } else if (keyPressed == '.'){ //When '.' pressed, do nothing
	
	            } else { //When Valid Key pressed, store the char
	                cout << keyPressed;
	                newExtension += keyPressed;
	            }
	        }
	
	        if(((int)keyPressed == 13 || (int)keyPressed == 32) && newExtension.length() > 0){
	            extensionsList.push_back(newExtension);
	            newExtension.clear();
	            cout << "\n";
	            counter++;
	            system("cls");
	        } else {
	        	// ERROR Effect
        		for(int i=0; i<4; i++){
        			system("color 0c");
        			system("color 0f");		
			}
			// END effect
	        	clear();
			}
	        if((int)keyPressed == 32){ // If space pressed, finish
	       		system("cls");
	            break;
	        }
	    }
	    
	    /* Creating the folder */
	    categoryFolder = "! -Personalizados- !";
	    if(backupPath == hereCondition){
	    	destinationPath = createDestinationPath(root, backupFolderName, categoryFolder, true);   
		}else{
			destinationPath = createDestinationPath(backupPath, backupFolderName, categoryFolder, true);  
		}

	    // Executing the instructions
	    system("color 08");
	    for(it = extensionsList.begin(); it != extensionsList.end(); ++it){
  	  		instruction = "for /r \u0022" + root + "\u0022 %x in (*." + extensionsList.back() + ") do copy \u0022%x\u0022 \u0022" + destinationPath; //destinationPath was cloned before
			system(instruction.c_str());
			extensionsList.pop_back();
			instruction.clear();
		}
	    
	    categoryFolder.clear();
	    destinationPath.clear();
	
															/*		Documents		*/
	
    } else if (selection == '2'){
		/* Creating the extensions array*/
		string documentsArray [10] = {"docx", "doc", "pdf", "pptx", "ppt", "xlsx", "xls", "txt", "rtf", "odt"};		
		
		/* Creating the folder */
	    categoryFolder = "! -Documentos- !";
	    if(backupPath == hereCondition){
	    	destinationPath = createDestinationPath(root, backupFolderName, categoryFolder, true);   
		}else{
			destinationPath = createDestinationPath(backupPath, backupFolderName, categoryFolder, true);  
		}
		
		/* Executing the instructions */
		system("color 08");
		for(int i=0; i<10; i++){
			instruction = "for /r \u0022" + root + "\u0022 %x in (*." + documentsArray[i] + ") do copy \u0022%x\u0022 \u0022" + destinationPath;
			system(instruction.c_str());
			instruction.clear();
		}
	
															/*		Audio		*/
	
    } else if (selection == '3'){
		/* Creating the extensions array*/
		string documentsArray [8] = {"mp3", "m4a", "flac", "wav", "wma", "aac", "amr", "ogg"};		
		
		/* Creating the folder */
	    categoryFolder = "! -Audio- !";
	    if(backupPath == hereCondition){
	    	destinationPath = createDestinationPath(root, backupFolderName, categoryFolder, true);   
		}else{
			destinationPath = createDestinationPath(backupPath, backupFolderName, categoryFolder, true);  
		}
		
		/* Executing the instructions */
		system("color 08");
		for(int i=0; i<10; i++){
			instruction = "for /r \u0022" + root + "\u0022 %x in (*." + documentsArray[i] + ") do copy \u0022%x\u0022 \u0022" + destinationPath;
			system(instruction.c_str());
			instruction.clear();
		}
	
															/*		Images		*/
	
    } else if (selection == '4'){
		/* Creating the extensions array*/
		string documentsArray [9] = {"jpg", "jpeg", "png", "gif", "psd", "webp", "bmp", "tiff", "raw"};		
		
		/* Creating the folder */
	    categoryFolder = "! -Imagenes- !";
	    if(backupPath == hereCondition){
	    	destinationPath = createDestinationPath(root, backupFolderName, categoryFolder, true);   
		}else{
			destinationPath = createDestinationPath(backupPath, backupFolderName, categoryFolder, true);  
		}
		
		/* Executing the instructions */
		system("color 08");
		for(int i=0; i<10; i++){
			instruction = "for /r \u0022" + root + "\u0022 %x in (*." + documentsArray[i] + ") do copy \u0022%x\u0022 \u0022" + destinationPath;
			system(instruction.c_str());
			instruction.clear();
		}
	
															/*		Video		*/
	
    } else if (selection == '5'){
		/* Creating the extensions array*/
		string documentsArray [10] = {"mp4", "3gp", "avi", "wmv", "gif", "mov", "flv", "mpg", "mpeg", "webm"};
		
		/* Creating the folder */
	    categoryFolder = "! -Video- !";
	    if(backupPath == hereCondition){
	    	destinationPath = createDestinationPath(root, backupFolderName, categoryFolder, true);   
		}else{
			destinationPath = createDestinationPath(backupPath, backupFolderName, categoryFolder, true);  
		}
		
		/* Executing the instructions */
		system("color 08");
		for(int i=0; i<10; i++){
			instruction = "for /r \u0022" + root + "\u0022 %x in (*." + documentsArray[i] + ") do copy \u0022%x\u0022 \u0022" + destinationPath;
			system(instruction.c_str());
			instruction.clear();
		}
	}
}

string priorizeOption1(string optionsSelected){
	char temp;
	if(optionsSelected[0] == '1'){
		return optionsSelected;
	} else if(optionsSelected.length() > 1){
		for(int i=1; i < optionsSelected.length(); i++){
			if(optionsSelected[i] == '1'){
				while(i != 0){
					temp = optionsSelected[i-1];
					optionsSelected[i-1] = '1';
					optionsSelected[i] = temp;
					i--;
				}
				return optionsSelected;
			}
		}
	} else {
		return optionsSelected;
	}
}

void charPause(char keyToPress){
	keyToPress = tolower(keyToPress);
	char keyPressed;
	cout << "\nPresione (" << keyToPress << ") para continuar . . .";
	while(true){
		keyPressed = getch();
		keyPressed = tolower(keyPressed);
		if(keyPressed == keyToPress) break;
	}
}

boolean thisCharExists(string input, char search){
	for(int i=0; i<input.length(); i++){
		if(input[i] == search){
			return true;	
		}
	}
	return false;
}

list<string> getDriveList(){
	list<string> driveList;
	
	char szBuffer[1024];
    ::GetLogicalDriveStrings(1024, szBuffer);
    char *pch = szBuffer;
    while (*pch) {
       driveList.push_back(pch);
       pch = &pch[strlen(pch) + 1];
    }
    return driveList;
}

string getDriveStr(){
	string driveStr;
	
	char szBuffer[1024];
    ::GetLogicalDriveStrings(1024, szBuffer);
    char *pch = szBuffer;
    while (*pch) {
       driveStr += pch;
       pch = &pch[strlen(pch) + 1];
    }
    return toLowerStr(driveStr);
}

boolean isValidPath(string path){
	if( (((int)path[0] <= 90 && (int)path[0] >= 65) || ((int)path[0] <= 122 && (int)path[0] >= 97)) && path.length() >= 3){
		if(path[1] == ':' && (path[2] == '/' || path[2] == '\u005C') ){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

int main() {
	/* Global Variables */
    SetConsoleTitle("Skrrap! 1.0 | By Shafool");
    char selection; selection = 'n';
    string backupFolderName, root, backupPath, instruction, destinationPath, optionsSelected, hereCondition;
    int counter = 1;
    char keyPressed;
    list<string> driveList;
    
    // Defining some G. Variables
    driveList = getDriveList();
    root = getRootPath() + "/";
    backupFolderName = "! - Archivos Extraidos -!";
    hereCondition = "aqui";
	backupPath = "";
	optionsSelected = "";
	
	// Intro sequence
	printLogo();
	
	for(int i=0; i<4; i++){
   		system("color 0d");
		system("color 0b");	
	}
	
	printInstructions(); system("timeout /t 10"); clear();
	// End
	
    while(true){
    	printLogo();
    	printMenu();
    	
    	cout << "\n   1) SELECCIONA TUS OPCIONES (Presiona espacio para terminar)\n"; 
   		printSelected(optionsSelected);
		cout << "\n";
        if(optionsSelected.length() != 0){
        	cout << "Agrega una opcion mas" << " >> ";
		} else {
			cout << "Agrega una opcion" << " >> ";
		}
        
        keyPressed=getch();
        if(((int)keyPressed == 32 || (int)keyPressed == 13) && optionsSelected.length() >0){ //When Space pressed, finish
            break;
        } else if ((int)keyPressed == 8){ //When Backspace pressed, clear
            optionsSelected = optionsSelected.substr(0, optionsSelected.length()-1);
            system("cls");
        } else if((int)keyPressed >= 48 && (int)keyPressed <= 57 && thisCharExists(optionsSelected, keyPressed) == false) { //When Valid Key pressed, store the char
            optionsSelected += keyPressed;
            system("cls");
        } else {
        	
        	// ERROR Effect
        	for(int i=0; i<4; i++){
        		system("color 0c");
        		system("color 0f");		
			}
			// END effect
			
        	system("cls");
		}
    }
    
    optionsSelected = priorizeOption1(optionsSelected);
    
    // Path selection
    color('0', 'd');
    while(true){
    	system("cls");
    	printLogo();
   		cout << "\n   1) OPCIONES SELECCIONADAS\n";
		printSelected(optionsSelected); cout << '\n';

		cout << "\n   2) INGRESA LA RUTA DE EXTRACCION\n";
		cout << "      1. Puedes copiar una RUTA especifica\n      2. Escojer una UNIDAD\n      3. Escribe AQUI para extraer en la ruta actual\n";
		cout << "      Unidades Disponibles: ";
	    list <string> :: iterator it; 
  		for(it = driveList.begin(); it != driveList.end(); ++it){
  	  		cout << *it << ' '; 
		}
		cout << '\n';
		
		// Path input zone
        cout << "Escribe la ruta" << " >> "; cin >> backupPath;
		if (isValidPath(backupPath) && thisCharExists(getDriveStr(), tolower(backupPath[0]))){ // Specified location
			clear();
			break;
		} else if (backupPath.length() == 1 && thisCharExists(getDriveStr(), tolower(backupPath[0]))){ // Drive letter selected
			// Prepare backupPath
			backupPath += ":\u005C";
			clear();
			break;
		} else if (toLowerStr(backupPath) == hereCondition){ // Extract in current location
			// Prepare backupPath
			backupPath = root;
			clear();
			break;
		} else {
			cout << "\n      [ Error ;D ] Ruta no existente \n\n";
			
			// ERROR Effect
        	for(int i=0; i<4; i++){
        		system("color 0c");
        		system("color 0d");	
			}
			// END effect
			
			system("pause");
		}
    }
    
    // Extract
    
    color('0', 'f');
	for(int i=0; i<optionsSelected.length(); i++){
    	extract(optionsSelected[i], root, backupPath, backupFolderName, optionsSelected, hereCondition);
	}
}
