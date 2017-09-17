#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

//обработчик COM порта
HANDLE hSerial;

IplImage* image = 0;
IplImage* templ[] = { 0, 0, 0, 0, 0 };

int main(int argc, char* argv[])
{
	//--------------------------------START COM-ports-------------------------------//
	// обьявляем COM порт
	LPCTSTR sPortName = L"COM6";

	hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	// разные ошибки, ну и фиг с ними
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("serial port does not exist.\n");
		}
		printf("some other error occurred.\n");
	}

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("getting state error\n");
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("error setting serial port state\n");
	}

	char data[] = { 'h' };  // строка для передачи
	DWORD dwSize = sizeof(data);   // размер этой строки
	DWORD dwBytesWritten;    // тут будет количество собственно переданных байт

	BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);

	printf(" %iBytes in string. %iBytes sended.\n", dwSize, dwBytesWritten);

	//------------------------------COM ports END!---------------------------------//



	// получаем любую подключённую камеру

	CvCapture* capture = cvCaptureFromCAM(0);//cvCreateCameraCapture(CV_CAP_ANY); 
	assert(capture);

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);//1280); 
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);//960); 


	/*
	// имя картинки задаётся первым параметром
	char* filename = argc >= 2 ? argv[1] : "viborka/image8-1.jpg";
	// получаем картинку
	image = cvLoadImage(filename, 1);
	printf("[i] image: %s\n", filename);
	assert(image != 0);*/

	// шаблон {кирпич - стоп - прямо - лево - право}
	char* _filename[] = { "_1.jpg", "_2.jpg", "_3.jpg", "_4.jpg", "_5.jpg", };

	for (int i = 0; i <= 4; i++) {
		printf("[i] template: %s\n", _filename[i]);
		templ[i] = cvLoadImage(_filename[i], 1);
		assert(templ[i] != 0);
	}

	// размер шаблона
	int width = templ[0]->width;
	int height = templ[0]->height;

	//cvNamedWindow("origianl", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("template", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("Match", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("res", CV_WINDOW_AUTOSIZE);

	// оригинал и шаблон
	//	cvShowImage("origianl", image);
	//	cvShowImage("template", templ[0]);
	// изображение для хранения результата сравнения
	// размер результата: если image WxH и templ wxh, то result = (W-w+1)x(H-h+1)
	IplImage *res = 0;
	// минимум и максимум на изображении
	double    minval, maxval;
	CvPoint    minloc, maxloc;

	// храним минимум для каждого шаблона
	double _max[] = { 0,0,0,0,0 };
	//номер минимального значения в массиве
	int mas_min = 0;
	double masm = 0;
	char sym_ardu = '9'; // символ для ардуино
	char sym_arduOld = '0'; // символ для ардуино

	while (true) {

		image = cvQueryFrame(capture);
		res = 0;
		mas_min = 0; masm = 0;

		for (int i = 0; i <= 4; i++) {
			// размер результата: если image WxH и templ wxh, то result = (W-w+1)x(H-h+1)
			res = cvCreateImage(cvSize((image->width - templ[0]->width + 1), (image->height - templ[0]->height + 1)), IPL_DEPTH_32F, 1);
			// сравнение изображения с шаблоном
			cvMatchTemplate(image, templ[i], res, CV_TM_CCORR_NORMED);
			// определение лучшее положение для сравнения
			// (поиск минимумов и максимумов на изображении)
			cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);
		//	printf("POROG: %f\n", maxval);
			_max[i] = maxval;

			if (maxval > masm) {
				masm = maxval;
				mas_min = i;
			}

			//покажем что получили
			//cvShowImage("res", res);

			// выделим область прямоугольником
			//cvRectangle(image, cvPoint(maxloc.x, maxloc.y), cvPoint(maxloc.x + templ[0]->width - 1, maxloc.y + templ[0]->height - 1), CV_RGB(255 - (i * 50), i * 30, 0), 1, 8);

			// показываем изображение
			//cvShowImage("Match", image);
			//cvWaitKey(0);
		}

		// порог для знака
		if (masm > 0.857) {
			//printf("Znak: %i\n", mas_min);
			masm = 0;
			switch (mas_min)
			{
			case 0:
				sym_ardu = '0';
				printf("KIRPIC\n");

				break;
			case 1:
				sym_ardu = '1';
				printf("STOP!!!\n");
				break;
			case 2:
				sym_ardu = '2';
				printf("VPERED!!!\n");
				break;
			case 3:
				sym_ardu = '3';
				printf("LEVO\n");
				break;
			case 4:
				sym_ardu = '4';
				printf("PRаVO\n");
				break;

			default:
				break;
			}
		}
		else {
			masm = 0;
			//printf("NO DETECT!!!\n");
			sym_ardu = '9';
		}

		if (sym_ardu != sym_arduOld) {
			data[0] = sym_ardu;  // строка для передачи
			dwSize = sizeof(data);   // размер этой строки
			dwBytesWritten;    // тут будет количество собственно переданных байт

			iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);

			printf(" %iBytes in string. %iBytes sended.\n", dwSize, dwBytesWritten);

			sym_arduOld = sym_ardu;
		}
		else {
			printf("--------------POVTOR!!!-------------\n");
		}

		char c = cvWaitKey(33);
		if (c == 27) { // если нажата ESC - выходим
			break;
		

	}
		// ждём нажатия клавиши

		//cvWaitKey(0);

	}
	// освобождаем ресурсы
	cvReleaseImage(&image);
	cvReleaseImage(&templ[0]);
	cvReleaseImage(&templ[1]);
	cvReleaseImage(&templ[2]);
	cvReleaseImage(&templ[3]);
	cvReleaseImage(&templ[4]);
	cvReleaseImage(&res);
	cvReleaseCapture(&capture);
	cvDestroyAllWindows();

	CloseHandle(hSerial); // закрытие COM порта
	return 0;
}