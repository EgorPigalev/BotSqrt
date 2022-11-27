#define SIZE_BUFFER 140

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int main()
{
	system("chcp 1251>null");
	LPSTR lpszPipiName = L"\\\\.\\pipe\\MyPipe1";

	HANDLE hNamePipe;
	DWORD size_buffer = SIZE_BUFFER;
	char message[SIZE_BUFFER];
	BOOL Connected;
	DWORD actual_readen;
	BOOL SeccessRead;
	while (TRUE)
	{
		hNamePipe = CreateNamedPipe(
			lpszPipiName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			SIZE_BUFFER,
			SIZE_BUFFER,
			INFINITE,
			NULL);
		Connected = ConnectNamedPipe(hNamePipe, NULL);
		if (Connected)
		{
			LPWSTR buffer = calloc(size_buffer, sizeof(CHAR));
			SeccessRead = ReadFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			if (SeccessRead)
			{
				printf("Клиент пишет: ");
				printf(buffer);
				printf("\n");
				/*char* istr[2];
				istr[0] = strtok(buffer, " ");
				int i = 0;
				while (istr != NULL)
				{
					i++;
					printf(" % s\n", istr);
					istr[1] = strtok(NULL, " ");
				}*/
				float a = atof(buffer);
				sprintf(message, "%g", a * a);
				LPWSTR b = (CHAR*)calloc(size_buffer, sizeof(CHAR));
				sprintf(b, "%s", buffer);
				LPWSTR c = (CHAR*)calloc(size_buffer, sizeof(CHAR));
				c = "0";
				if (a == 0 && strcmp(b, c) != 0)
				{
					sprintf(message, "Я вас не понимаю");
				}
				/*
				if (i > 2)
				{
					sprintf(message, L"Я вас не понимаю");
				}
				*/
				//printf("\nВведите сообщение для клиента: \n");
				//gets(message);

				buffer = &message;
				WriteFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			}
		}
		else
		{
			printf("\nКлиент отключился от сервера\n");
		}
		CloseHandle(hNamePipe);
	}
}