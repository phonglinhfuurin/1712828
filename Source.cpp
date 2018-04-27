#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<cstdlib>
#include<conio.h>
#include<wchar.h>
#include <fcntl.h> 
#include <io.h> 

struct SV{
	wchar_t *MSSV;
	wchar_t *hoten;
	wchar_t *khoa;
	int	namhoc;
	wchar_t *ngaysinh;
	 
	wchar_t *email;
	wchar_t *hinh;
	wchar_t *mota;
	wchar_t *sothich;
};
wchar_t *readLine(FILE *fin)
{
	wchar_t buff[2048];
	fgetws(buff, 2048, fin);
	wchar_t *token = wcstok(buff, L"\n");
	wchar_t *line = (wchar_t*)calloc(2048, sizeof(wchar_t));
	wcscpy(line, token);
	return line;
	free(line);
}

wchar_t *Copy_String(wchar_t *dest, wchar_t *sub)

{

	wchar_t *ps = &dest[0];  

	while (*sub){ *dest++ = *sub++; }  

	return ps; wprintf(L"cp3");

}
int myAtoi(wchar_t *str)
{
	int res = 0; 
	for (int i = 0; str[i] != '\0'; i++)
		res = res * 10 + str[i] - '0';
	return res;
}
wchar_t* XoaNgoacKep(wchar_t* line)
{
	wchar_t *newLine =(wchar_t*)calloc(wcslen(line),sizeof(wchar_t));
	size_t i, j;
	if (line[0] != '\"')
		newLine[0] = line[0];
	for (i = j = 1; i < wcslen(line); i++)
	{
		if (line[i] == '\"' && line[i - 1] != '\\')
			continue;
		newLine[j++] = line[i];
	}
 
	return newLine; 
	free(newLine);

}



void Get_Part(wchar_t *line, SV *sv)
{
	const wchar_t *s = L","; wprintf ;
	wchar_t *token; wprintf(L"2");

	token = wcstok(line, s); wprintf;
	sv->MSSV = (wchar_t*)calloc(15, sizeof(wchar_t));
	wcscpy(sv->MSSV, token); wprintf;

	token = wcstok(NULL, s); wprintf;
	sv->hoten = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->hoten, token);  wprintf;


	token = wcstok(NULL, s);
	sv->khoa = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->khoa, token);  wprintf(L"4");


	token = wcstok(NULL, s);
	sv->namhoc = myAtoi(token); 

	token = wcstok(NULL, s);
	sv->ngaysinh = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->ngaysinh, token);  wprintf(L"4");
	
	token = wcstok(NULL, s);
	sv->email = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->email, token);  wprintf(L"4");

	token = wcstok(NULL, s);
	sv->hinh = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->hinh, token);  wprintf(L"6");

	token = wcstok(NULL, s);
	sv->mota = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->mota, token);

	token = wcstok(NULL, L"\n");


	 if (token != NULL){
		 wchar_t *buff = (wchar_t*)calloc(2048, sizeof(wchar_t));
		sv->sothich = (wchar_t*)calloc(50, sizeof(wchar_t));  
		wcscpy(buff,token);
		wchar_t* tokensub;
		tokensub = wcstok(buff, L",");
		while (tokensub!=NULL)
		{
			wcscat(sv->sothich, L"- ");
			wcscat(sv->sothich, tokensub); 
			wcscat(sv->sothich, L"\n"); 
			tokensub = wcstok(NULL, L","); 
		}
		free(buff);
	}

}
wchar_t *Replacestr(wchar_t *strtext, wchar_t *find, wchar_t *replace)
{
	wchar_t *newbuff = (wchar_t*)calloc((wcslen(strtext) - wcslen(find) + wcslen(replace) + 1), sizeof(wchar_t));
	wchar_t *ptr;

	wcscpy(newbuff, strtext);
	ptr = wcsstr(newbuff, find);
	if (ptr)
	{
		wmemmove(ptr + wcslen(replace), ptr + wcslen(find), wcslen(ptr + wcslen(find)) + 1);
		wcsncpy(ptr, replace, wcslen(replace));
	}

	return newbuff;
}
wchar_t * GetStr_2delim(wchar_t *str, wchar_t *p1, wchar_t *p2)
{
	wchar_t *i1 = wcsstr(str, p1);  
	if (i1 != NULL)
	{ 
		size_t pl1 = wcslen(p1);
		wchar_t *i2 = wcsstr(i1 + pl1, p2);
		if (p2 != NULL)
		{
			 
			size_t mlen = i2 - (i1 + pl1);
			wchar_t *ret = (wchar_t*)calloc(mlen + 1,sizeof(wchar_t));
			if (ret != NULL)
			{
		 
				wmemcpy(ret, i1 + pl1, mlen);
				ret[mlen] = '\0';
				return ret;
			}
		}
	}
}

void writeHTML(FILE *finHTML, FILE *fout, SV *sv)
{ 
	wchar_t*buffcon = (wchar_t*)calloc(20, sizeof(wchar_t));
	wchar_t* str = (wchar_t*)calloc(2048, sizeof(wchar_t));
	wchar_t *newstr = (wchar_t*)calloc(2048, sizeof(wchar_t));
	wchar_t* minibuff = (wchar_t*)calloc(1024, sizeof(wchar_t));
	rewind(finHTML);
	while (!feof(finHTML)) {
		wprintf(L"------ ");
		fgetws(str, 2048, finHTML);
		if (wcsstr(str, L"<title>HCMUS -") != NULL)
		{
			buffcon = GetStr_2delim(str, L"HCMUS - ", L"</title>");
			wcscpy(newstr, Replacestr(str, buffcon, sv->hoten));
			fputws(newstr, fout);
			wprintf(L"%s", newstr);
			continue;

		};

		if (wcsstr(str, L"=\"Personal_FullName\">") != NULL)
		{
			buffcon = GetStr_2delim(str, L"Personal_FullName\">", L"</div>");
			wcscat(minibuff, sv->hoten);
			wcscat(minibuff, L" - ");
			wcscat(minibuff, sv->MSSV);
			wcscpy(newstr, Replacestr(str, buffcon, minibuff));
			wprintf(L"%s", newstr);
			fputws(newstr, fout);
			continue;
		};

		if (wcsstr(str, L"=\"Personal_Department\">") != NULL)
		{
			buffcon = GetStr_2delim(str, L"Personal_Department\">", L"</div>");
			wcscpy(newstr, Replacestr(str, buffcon, sv->khoa));
			wprintf(L"%s", newstr);
			fputws(newstr, fout);
			continue;
		};

		if (wcsstr(str, L"src=\"") != NULL)
		{
			buffcon = GetStr_2delim(str, L"src=\"", L"\"");
			wcscpy(newstr, Replacestr(str, buffcon, sv->hinh));
			wprintf(L"%s", newstr);
			fputws(newstr, fout);
			continue;
		}

		if (wcsstr(str, L"src=\"") != NULL)
		{
			buffcon = GetStr_2delim(str, L"src=\"", L"\"");
			wcscpy(newstr, Replacestr(str, buffcon, sv->hinh));
			wprintf(L"%s", newstr);
			fputws(newstr, fout);
			continue;
		}
		if (wcsstr(str, L"<li>Họ và tên:") != NULL)
		{
			buffcon = GetStr_2delim(str, L"<li>Họ và tên:", L"</li>");
			wcscpy(newstr, Replacestr(str, buffcon, sv->hoten));
			wprintf(L"%s", newstr);
			fputws(newstr, fout);
			continue;
		}
		if (wcsstr(str, L"<li>MSSV:") != NULL)
		{
			buffcon = GetStr_2delim(str, L"<li>MSSV:", L"</li>");
			wcscpy(newstr, Replacestr(str, buffcon, sv->MSSV));
			wprintf(L"%s", newstr);
			fputws(newstr, fout);
			continue;
		}
		else
		{
			fputws(str, fout);
			wprintf(L"%s", str);
		};

	}

}





void main()

{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	wchar_t data;
	FILE* fin = _wfopen(L"thongtinsv.CSV", L"rt, ccs=UTF-8");
	if (!fin)
	{
		wprintf(L"Không mở được file thongtinsv.CSV");
		fclose(fin);
		return;
	}
	wchar_t buff[2048];
	wchar_t buffHTML[2048];
	FILE* fileOut = _wfopen(L"profilepage.html", L"wt, ccs=UTF-8");
	int soluontest = 0;
	while (!feof(fin))
	{
		fgetws(buff, 2048, fin);
		wprintf(L" line: %ls", buff);
	}
	rewind(fin);
	wchar_t *line;
	line = readLine(fin);
	wchar_t *line_chuan; 
	line_chuan = XoaNgoacKep(line);
	wprintf(L"%s" , line_chuan);
	rewind(fin);
	wchar_t *sothich;
	FILE* finHTML = _wfopen(L"FileHTML.html", L"rt, ccs=UTF-8");
	if (!(finHTML))
	{
		wprintf(L"Không mở được file FileHTML.html");
		fclose(finHTML);
		return;
	}
	rewind(finHTML);
	while (!feof(finHTML))
	{
		fgetws(buffHTML, 2048, finHTML);
		fwprintf(fileOut, buff);
	}
	rewind(finHTML);
	SV *sv=(SV*)calloc(10,sizeof(SV));
	Get_Part(line_chuan, sv);
	wprintf(L"%ls %ls %ls %ls %ls %ld %ls %ls so thich %ls", sv->MSSV, sv->hoten, sv->khoa,sv->ngaysinh,sv->email,sv->namhoc, sv->hinh,sv->mota, sv->sothich);
	rewind(finHTML);
	writeHTML(finHTML, fileOut, sv);
	fclose(fin);
	fclose(fileOut);
}
