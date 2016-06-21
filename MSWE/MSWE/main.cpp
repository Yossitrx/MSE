
#include <Windows.h>
#include <stdio.h>
#include "ComboBox.h"
#include "TextBox.h"
#include "Button.h"
#include "NumericBox.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR lpszMessage);


struct ExListener : public MouseListener {
	void MousePressed(IControl &b, int x, int y, bool isLeft) {
		if (isLeft) {
			COORD crd = { x,y };
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(handle, crd);
			DWORD dw = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			SetConsoleTextAttribute(handle, dw);
			cout << "bla bla!!!";
		}
	}
};


int main() {

	ExListener func;


	DWORD dw = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	vector<string> list = {
		"line 1",
		"line 2",
		"line 3",
		"line 4",
		"line 5"
	};

	//////////////////////////////////////////////////////////////////   ~MAIN~    /////////////////////////////////////////////////////////////////////////////////////////////// 


	/* to test one of the controllers comment the "Label main" and un-commet the requested controller */


	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//				 Label   	 			//
	//										//
	//										//
	//////////////////////////////////////////

	//Label label = Label(40, "Eyal & Ron & Yossi");
	//label.SetForeground(ForegroundColor::White);
	//label.SetCoordinates(20, 10);
	//label.Show();
	//Sleep(2222);

	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//				ComboBox				//
	//										//
	//										//
	//////////////////////////////////////////

	//ComboBox combo = ComboBox(15, list);
	//combo.SetForeground(ForegroundColor::White);
	//combo.SetBackground(BackgroundColor::Blue);
	//combo.SetBorder(BorderType::None);
	//combo.SetCoordinates(0, 3);
	//combo.Show();
	//Sleep(2222);
	//combo.Hide();

	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//				RadioList				//
	//										//
	//										//
	//////////////////////////////////////////

	//RadioList radio = RadioList(5, 15, list);
	//radio.SetForeground(ForegroundColor::Red);
	//radio.SetBackground(BackgroundColor::Black);
	//radio.SetBorder(BorderType::Double);
	//radio.SetCoordinates(0, 10);
	//radio.Show();
	//Sleep(2222);
	//radio.Hide();

	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//				CheckList				//
	//										//
	//										//
	//////////////////////////////////////////

	//CheckList check = CheckList(5, 15, list);
	//check.SetForeground(ForegroundColor::Purple);
	//check.SetBackground(BackgroundColor::White);
	//check.SetBorder(BorderType::Single);
	//check.SetCoordinates(0, 18);
	//check.Show();
	//Sleep(2222);
	//check.Hide();

	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//				TextBox			     	//
	//										//
	//										//
	//////////////////////////////////////////

	//TextBox text = TextBox(5);
	//text.SetCoordinates(20, 5);
	//text.SetBackground(BackgroundColor::White);
	//text.SetForeground(ForegroundColor::Blue);
	//text.SetBorder(BorderType::Single);
	//text.Show();

	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//				Button			     	//
	//										//
	//										//
	//////////////////////////////////////////

	//Button button = Button(10);
	//button.SetForeground(ForegroundColor::White);
	//button.SetBackground(BackgroundColor::Blue);
	//button.SetCoordinates(30, 10);
	//button.SetBorder(BorderType::None);
	//button.SetValue("TEAM");
	//button.AddListener(&func);

	//button.Show();
	//Sleep(2222);
	//button.Hide();

	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//			   NumericBox    	     	//
	//										//
	//										//
	//////////////////////////////////////////

	NumericBox numericBox = NumericBox(20, 5, 30);
	numericBox.SetValue(10);
	numericBox.SetCoordinates(30, 10);
	numericBox.SetForeground(ForegroundColor::White);
	numericBox.SetBackground(BackgroundColor::Blue);
	numericBox.SetBorder(BorderType::None);

	numericBox.Show();
	//Sleep(2222);
	//NumericBox.Hide();

	//////////////////////////////////////////
	//										//
	//										//
	//										//
	//			     ALL     		     	//
	//										//
	//										//
	//////////////////////////////////////////


	//combo.Show();
	//radio.Show();
	//text.Show();
	//check.Show();
	//label.Show();




	//////////////////////////////////////////////////////////////////   ~MAIN~    /////////////////////////////////////////////////////////////////////////////////////////////// 


	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];




	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 
	while (true)
	{
		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++) {
			//Send the input record to the textbox handler
			//radio.HandleInput(irInBuf[i]);
			//check.HandleInput(irInBuf[i]);
			//text.HandleInput(irInBuf[i]);
			//radio.HandleInput(irInBuf[i]);
			//button.HandleInput(irInBuf[i]);
			numericBox.HandleInput(irInBuf[i]);
		}
	}


	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	return 0;
}

void ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}