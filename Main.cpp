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
	wchar_t *newLine =(wchar_t*)calloc(256,sizeof(wchar_t));
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
	const wchar_t *s = L","; 
	wchar_t *token; 

	token = wcstok(line, s);  
	sv->MSSV = (wchar_t*)calloc(15, sizeof(wchar_t));
	wcscpy(sv->MSSV, token); wprintf;

	token = wcstok(NULL, s);  
	sv->hoten = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->hoten, token);   


	token = wcstok(NULL, s);
	sv->khoa = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->khoa, token);   


	token = wcstok(NULL, s);
	sv->namhoc = myAtoi(token); 

	token = wcstok(NULL, s);
	sv->ngaysinh = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->ngaysinh, token);   
	
	token = wcstok(NULL, s);
	sv->email = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->email, token);  

	token = wcstok(NULL, s);
	sv->hinh = (wchar_t*)calloc(30, sizeof(wchar_t));
	wcscpy(sv->hinh, token);   

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
	 /* free(sv->email); free(sv->hinh); free(sv->hoten); free(sv->khoa); free(sv->mota); free(sv->MSSV);
	 free(sv->ngaysinh); free(sv->sothich);*/

}
wchar_t *Replacestr(wchar_t *strtext, wchar_t *find, wchar_t *replace)
{
	wchar_t *newbuff = (wchar_t*)calloc(1024, sizeof(wchar_t));
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
			wchar_t *ret = (wchar_t*)calloc(mlen,sizeof(wchar_t));
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
	rewind(finHTML);
	//wchar_t*buffcon = (wchar_t*)calloc(256, sizeof(wchar_t));
	//wchar_t buffcon[40];
	wchar_t*buffcon = (wchar_t*)calloc(1024, sizeof(wchar_t));
	wchar_t *newstr = (wchar_t*)calloc(2048 + 1024, sizeof(wchar_t));
	wchar_t* str = (wchar_t*)calloc(2048, sizeof(wchar_t));
	wchar_t* minibuff = (wchar_t*)calloc(256, sizeof(wchar_t));
	while (!feof(finHTML)) {
		//wprintf(L"------ ");   
		fgetws(str, 2048, finHTML);
		if (wcsstr(str, L"<title>HCMUS -") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"HCMUS - ", L"</title>"), sv->hoten));
			fputws(Replacestr(str, GetStr_2delim(str, L"HCMUS - ", L"</title>"), sv->hoten), fout);
			continue;
		}

		if (wcsstr(str, L"=\"Personal_FullName\">") != NULL)
		{
			wcscpy(buffcon, GetStr_2delim(str, L"Personal_FullName\">", L"</div>"));
			wcscat(minibuff, sv->hoten);
			wcscat(minibuff, L" - ");
			wcscat(minibuff, sv->MSSV);
			wcscpy(newstr, Replacestr(str, buffcon, minibuff));
			wprintf(L"%s", newstr);
			fputws(newstr, fout);
			free(minibuff);
			continue;
		}

		if (wcsstr(str, L"Personal_Department\">") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"Personal_Department\">", L"</div"), sv->khoa));
			continue;
		}

		if (wcsstr(str, L"src=\"") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"src=\"", L"\""), sv->hinh));
			fputws(Replacestr(str, GetStr_2delim(str, L"src=\"", L"\""), sv->hinh), fout);
			continue;
		}

		if (wcsstr(str, L"<li>Họ và tên:") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"<li>Họ và tên:", L"</li>"), sv->hoten));
			fputws(Replacestr(str, GetStr_2delim(str, L"<li>Họ và tên:", L"</li>"), sv->hoten), fout);
			continue;
		}
		if (wcsstr(str, L"<li>MSSV:") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"<li>MSSV: ", L"</li>"), sv->MSSV));
			fputws(Replacestr(str, GetStr_2delim(str, L"<li>MSSV: ", L"</li>"), sv->MSSV), fout);
			continue;
		}
		if (wcsstr(str, L"<li>Sinh viên khoa ") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"<li>Sinh viên khoa ", L"</li>"), sv->khoa));
			fputws(Replacestr(str, GetStr_2delim(str, L"<li>Sinh viên khoa ", L"</li>"), sv->khoa), fout);
			continue;
		}
		if (wcsstr(str, L"<li>Ngày sinh: ") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"<li>Ngày sinh: ", L"</li>"), sv->ngaysinh));
			fputws(Replacestr(str, GetStr_2delim(str, L"<li>Ngày sinh: ", L"</li>"), sv->ngaysinh), fout);
			continue;
		}
		if (wcsstr(str, L"Email:") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"Email:", L"\n"), sv->email));
			fputws(Replacestr(str, GetStr_2delim(str, L"Email:", L"\n"), sv->email), fout);
			continue;
		}
		if (wcsstr(str, L"Email:") != NULL)
		{
			wprintf(L"%s", Replacestr(str, GetStr_2delim(str, L"Email:", L"</li>"), sv->email));
			fputws(Replacestr(str, GetStr_2delim(str, L"Email:", L"</li>"), sv->email), fout);
			continue;
		}
		if (wcsstr(str, L"Sở thích") != NULL)
		{
			wprintf(L"%s", str);
			fputws(str, fout);
			while (wcsstr(str, L"TextInList") == NULL){
				feof(fout);
				fgetws(str, 2048, finHTML);
				wprintf(L"%s", str);
				fputws(str, fout);
			}
			wchar_t *token;
			token = wcstok(sv->sothich, L"\n");
			while (token != NULL)
			{
				wprintf(L"%s %s %s", L"\t\t\t\t\t<li>", token, L"</li>\n");
				fputws(L"\t\t\t\t\t<li>", fout);
				fputws(token, fout);
				fputws(L"</li>\n", fout);
				token = wcstok(NULL, L"\n");
			}

			while (wcsstr(str, L"</ul>") == NULL)
			{
				feof(finHTML);
				fgetws(str, 2048, finHTML);
			}
			wprintf(L"%s", str);
			fputws(str, fout);
			continue;
		}
		if (wcsstr(str, L"Description\">") != NULL)
		{
			wprintf(L"%s", str);
			fputws(str, fout);
			feof(finHTML);
			wprintf(L"\t\t\t\t\t%s \n", sv->mota);
			fputws(L"\t\t\t\t\t", fout);
			fputws(sv->mota, fout);
			fputws(L" \n", fout);
			while (wcsstr(str, L"</div>") == NULL)
			{
				feof(finHTML);
				fgetws(str, 2048, finHTML);
			}
			wprintf(L"%s", str);
			fputws(str, fout);
			continue;
		}
		if (wcsstr(str, L"TH2012/03</br>") != NULL)
		{
			wprintf(L"%s", str);
			fputws(str, fout);
			feof(finHTML);
			wprintf(L"\t\t\t%s - %s </br> \n", sv->MSSV, sv->hoten);
			fputws(L"\t\t\t\t\t", fout);
			fputws(sv->MSSV, fout);
			fputws(sv->hoten, fout);
			fputws(L" \n", fout);
			while (wcsstr(str, L"</div>") == NULL)
			{
				feof(finHTML);
				fgetws(str, 2048, finHTML);
			}
			wprintf(L"%s", str);
			fputws(str, fout);
			continue;
		}
		wprintf(L"%s", str);
		fputws(str, fout);

	}
	 free(str);
	 free(newstr);
	 free(buffcon);
}

void main()

{

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	wchar_t data;
	wchar_t buff[2048];
	wchar_t buffHTML[2048];
	int soluongsinhvien = 0;

	FILE* fin = _wfopen(L"thongtinsv.CSV", L"rt, ccs=UTF-8");
	if (!fin)
	{
		wprintf(L"Không mở được file thongtinsv.CSV");
		fclose(fin);
		return;
	}
	 
	FILE* fileOut = _wfopen(L"profilepage.html", L"wt, ccs=UTF-8");

 	while (!feof(fin))
	{
		fgetws(buff, 2048, fin);   
		wprintf(L" line: %ls", buff);         // doc tung dong va dem so luong sinh vien
		soluongsinhvien++;
	}
	 
	rewind(fin);

	FILE* finHTML = _wfopen(L"FileHTML.html", L"rt, ccs=UTF-8");
	if (!(finHTML))
	{
		wprintf(L"Không mở được file FileHTML.html");
		fclose(finHTML);
		return;
	}
	rewind(finHTML);

	
	int dem = 0;
	while (dem < soluongsinhvien -1)
	{   
		wchar_t *line = (wchar_t*)calloc(2048, sizeof(wchar_t));
		line = readLine(fin); 
		wchar_t *line_chuan = (wchar_t*)calloc(2048, sizeof(wchar_t));
		wcscpy(line_chuan, XoaNgoacKep(line));
		wprintf(L"\n%s \n", line_chuan ); 
		wprintf(L"------");
		SV *sv = (SV*)calloc(10, sizeof(SV));
		Get_Part(line_chuan, sv);
		//rewind(fin);
		wchar_t* Makefilename = (wchar_t*)calloc(256, sizeof(wchar_t));
		wcscpy(Makefilename, sv->hoten);
		wcscat(Makefilename, L".html");
		FILE* fileOut = _wfopen(Makefilename, L"wt, ccs=UTF-8");
		//rewind(fin);
		writeHTML(finHTML, fileOut, sv);
		free(line);
		free(Makefilename);
		free(line_chuan);
		dem++;
		wprintf(L"SINH VIEN THU %d", dem);
	} 
	fclose(finHTML);
	fclose(fin);
	fclose(fileOut);
}
