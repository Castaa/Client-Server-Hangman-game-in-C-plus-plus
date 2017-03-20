#include"stdafx.h"

#include "inflate.h"

using namespace std;


// loads contents from a zipped compressed dictionary file
bool LoadWordFile(vector<string>& wordVector)
{
  // 32K buffer
  #define MAX_LEN 0x8000

  LUFILE*    zf = nullptr;
  DWORD e;    // for debug use

  zf = lufopen("dictionary.data",0,2,&e);
  if (zf == nullptr)
  {
    return false;
  }

  BYTE* buf = nullptr;
  char szCurFileName[UNZ_MAXFILENAMEINZIP+1];

  buf = new BYTE[MAX_LEN]; // create temp buffer for loading data from compressed data file

  unzFile uf = unzOpenInternal(zf); // there is a gotofirstfile in the end
          string tempStr;
  if(!uf)
  {
    delete [] buf;
    buf = nullptr;
    return false;
  }

  int err = unzGoToFirstFile(uf);

  while( err == UNZ_OK )
  {
    unzGetCurrentFileInfo(uf,nullptr,szCurFileName,
           sizeof(szCurFileName)-1,nullptr,0,nullptr,0);
    int n = lstrlenA(szCurFileName)-1;
    unzOpenCurrentFile(uf);
    bool haderr = false;

    do
    { 
      int res = unzReadCurrentFile( uf, buf, MAX_LEN );  // read in a chunk of a file in the zip

      if( res < 0 ) 
      {
        haderr = true; 
        break;
      }
      if( res == 0 )
      {
        break;
      }

      int currStrLength = 0;
      unsigned char *pbuf = buf;
      // parse strings from raw buffer from zip file
      for( int i=0; i < res; i++, pbuf++ )
      {
        if( *pbuf == ' ' )
        {
          // we've hit the end of the word, add the string to our vector
          tempStr.append((char*)(pbuf-currStrLength), currStrLength); // through pointer athrimethetic, move back in the buffer at the start of the word to add it to our string
          wordVector.push_back(tempStr);
          currStrLength = 0;
          tempStr.clear();
        }
        else
        {
          currStrLength++;
        }

      }
    } while(true);

    err = unzGoToNextFile(uf);
  }

  delete [] buf;
  buf = nullptr;

  if( wordVector.empty() )
  {  
    return false;
  }
  return true;
}