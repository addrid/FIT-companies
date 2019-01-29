#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
#endif /* __PROGTEST__ */

class CCompanyIndex
 {
   public:
                             CCompanyIndex ( void );
							 ~CCompanyIndex ( void );

    bool                     Add           ( const string & oName,
                                             const string & oAddr,
                                             const string & cName,
                                             const string & cAddr );

    bool                     Del           ( const string & oName,
                                             const string & oAddr );

    bool                     Search        ( const string & oName,
                                             const string & oAddr,
                                             string       & cName,
                                             string       & cAddr ) const;

	bool                     BinarySearch  ( const string       & cName,
                                             const string       & cAddr, 
											 int          & position ) const;


	void                     PrintArr      ( void );
	void                     AppendArr     ( void );

	struct TRec
	{
		string oName, oAddr;
	    string cName, cAddr;
	};
	
 private :
	
	TRec ** db; // databaze
	int len; // delka databaze
	int size; // delka pro alokovani

 };


CCompanyIndex :: CCompanyIndex ( void )
{
		size = 1000;
        db = new TRec * [size]; 
		//db[0] = new TRec;
		len = 0;
}

CCompanyIndex :: ~CCompanyIndex ( void )
{
	int i;
    /*for ( i = 0 ; i < len ; i ++ )
		delete db[i];*/
    delete [] db;
}

void CCompanyIndex :: PrintArr ()
{
	int i;
	for ( i = 0; i < len ; i++ )
	{
		cout << endl;
		cout << "oName: " << db[i]->oName << endl;
		cout << "oAddr: " << db[i]->oAddr << endl;
		cout << "cName: " << db[i]->cName << endl;
		cout << "cAddr: " << db[i]->cAddr << endl;
		cout << "*----------------------*" << endl;
    }
}

void CCompanyIndex :: AppendArr () 
 {
	 size += size;
	 TRec ** newDb = new TRec * [size];
	 
	 for (int i = 0; i < len; i++) 
	 {
		 newDb[i] = db[i];
	 }
	 delete [] db;
	 db = newDb;
 }

bool CCompanyIndex :: Add ( const string & oName, const string & oAddr,
						    const string & cName, const string & cAddr )
{
	int i = 0;
	int position;
	TRec * tmp;
	TRec * record = new TRec;
		record->oName = oName;
		record->oAddr = oAddr;
		record->cName = cName;
		record->cAddr = cAddr;

    if (len == 0)
	{
		db[0] = record;
		len ++;

		return true;
	}

	if ( BinarySearch ( oName, oAddr, position ) )
	{
		// Zaznam uz je obsazen v poli
		return false;
	}

	if ( len  == size-1 )
	{
		AppendArr();
	}

	for ( i = position ; i <= len ; i ++ )
	{
		tmp = db[i];
		db[i] = record;
		record = tmp;
	}
	len ++;
	return true;
}

bool CCompanyIndex :: Del ( const string & oName, const string & oAddr )
{
	int i = 0;
	int position;

	if ( !BinarySearch ( oName, oAddr, position ) )
	{
		return false;
	}
	//delete db[i];
	for ( i = position ; i < len ; i ++)
	{
		db[i] = db[i+1];
	}
	
	
	len--;
	return true;
}
bool CCompanyIndex :: Search ( const string & oName, const string & oAddr,
						             string & cName, string & cAddr ) const
{
	int position;

	if ( !BinarySearch ( oName, oAddr, position ) )
	{
		return false;
	}
	else
	{
		cName = db[position] ->cName;
		cAddr = db[position] ->cAddr;
		return true;
	}

}

bool CCompanyIndex :: BinarySearch ( const string & oName, 
									 const string & oAddr,
								     int & position ) const
{
	int first = 0, last = len-1, middle;
	//string key = oName + oAddr;
	//string merged = "";
	
	while (first <= last) 
	{
		middle = (first + last) / 2;  // prostredni pozice
		//merged = db[middle]->oName + db[middle]->oAddr; 
        //result = merged.compare(key); // porovnavam oba spojeny stringy

		if ( oAddr == db[middle]->oAddr && oName == db[middle]-> oName ) // proseminar 3
		{ // zaznam nalezen
			position = middle;
			return true;
		}

        if ( oName == db[middle] -> oName ) // hledany ma stejny oName ...
		{
			if ( oAddr < db[middle] -> oAddr)// ... ale odlisnou adresu (hledana je pred)
			{
			     last = middle - 1;	
			}
			else
				 first = middle + 1;
		}
		else 
		{     
			if ( oName < db[middle] -> oName ) // hledany abecedne pred middle prvkem
			{
				last = middle - 1 ; 
			}
			else    // hledany abecedne za middle prvkem
			{
				first = middle + 1 ;
			}
		}
     }
	 position = first;
	 return false;
}


#ifndef __PROGTEST__
int main (void)
{
	bool   status;	
	string cName, cAddress;
	CCompanyIndex  b1;

	status = true;
	/*
	string a = "abcd";
	string b = "zsdasd";

	if ( a > b )
		cout << "a vetsi" << endl;
	else
		cout << "b vetsi" << endl;
	*/
	/*
	status = b1 . Add ( "Smith", "Oak road", "ACME, Ltd.", "One ACME road" );
	status = b1 . Add ( "Barom", "Oak road", "ACME, Ltd.", "One ACME road" );
	status = b1 . Add ( "Koko", "Oak road", "ACME, Ltd.", "One ACME road" );
	status = b1 . Add ( "Margoh", "Oak road", "ACME, Ltd.", "One ACME road" );
	status = b1 . Add ( "Zeel", "Oak road", "ACME, Ltd.", "One ACME road" );
	status = b1 . Add ( "Arab", "Oak road", "ACME, Ltd.", "One ACME road" );
	status = b1 . Add ( "Klisna", "Oak road", "ACME, Ltd.", "One ACME road" );
	status = b1 . Add ( "Postak", "Oak road", "ACME, Ltd.", "One ACME road" );

	b1.PrintArr ();*/
/*

	
	status = b1 . Add ( "Smith", "Oak road", "ACME, Ltd.", "One ACME road" );
// status = true
	cout << status << endl;
	
	status = b1 . Add ( "Brown", "Second street", "MakroHard, Inc.", "Soft street" );
// status = true
	cout << status << endl;
	
	status = b1 . Add ( "Hacker", "5-th avenue", "Forks and Knives, Ltd.", "Cutlery avenue" );
// status = true
	cout << status << endl;
	
	status = b1 . Add ( "Hacker", "7-th avenue", "Child toys, Inc.", "Red light district" );
// status = true
	cout << status << endl;

	status = b1 . Search ( "Brown", "Second street", cName, cAddress );
// status = true, cName = "MakroHard, Inc.", cAddress="Soft street"
   cout << "status = " << status << " cName = " << cName << "cAddress = " << cAddress << endl;

status = b1 . Search ( "Hacker", "Oak road", cName, cAddress );
// status = false
	cout << status << endl;

	status = b1 . Search ( "Smith", "Oak road", cName, cAddress );
// status = true, cName = "ACME, Ltd.", cAddress="One ACME road"
	cout << "status = " << status << " cName = " << cName << "cAddress = " << cAddress << endl;

	status = b1 . Del ( "Smith", "Oak road" );
// status = true
	cout << status << endl;

	status = b1 . Search ( "Smith", "Oak road", cName, cAddress );
// status = false
	cout << status << endl;

	

	
	b1.PrintArr();
	*/
	
	/*


	CCompanyIndex  b2;
	status = b2 . Add ( "Smith", "Michigan avenue", "ACME, Ltd.", "One ACME road" );
	// status = true
	cout << status << endl;
	
	status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
	// status = true, cName = "ACME, Ltd.", cAddress="One ACME road"
	cout << "status = " << status << " cName = " << cName << "cAddress = " << cAddress << endl;
	
	status = b2 . Del ( "Smith", "Michigan avenue" );
	// status = true
	cout << status << endl;
	
	status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
	// status = false
	cout << status << endl;
	
	status = b2 . Del ( "Smith", "Michigan avenue" );
	// status = false
	cout << status << endl;
	
	status = b2 . Add ( "Smith", "Michigan avenue", "Forks and Knives, Ltd.", "Cutlery avenue" );
	// status = true
	cout << status << endl;
	
	status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
	// status = true, cName = "Forks and Knives, Ltd.", cAddress="Cutlery avenue"
	cout << "status = " << status << " cName = " << cName << "cAddress = " << cAddress << endl;
	
	status = b2 . Add ( "Smith", "Michigan avenue", "Child toys, Inc.", "Red light district" );
	// status = false
	cout << status << endl;
	
	status = b2 . Add ( "Smith", "Michigan avenue", "MakroHard, Inc.", "Soft street" );
	// status = false
	cout << status << endl;
	
	status = b2 . Del ( "Smith", "Michigan avenue" );
	// status = true
	cout << status << endl;
	
	status = b2 . Search ( "Smith", "Michigan avenue", cName, cAddress );
	// status = false
	cout << status << endl;

	

	//b2.PrintArr();
	*/

	system("PAUSE");
	return 0;

}
#endif /* __PROGTEST__ */