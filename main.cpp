#include<iostream>

using namespace std;


class LongInt {

    private:

        struct digit {

            int d_val;

            digit *more, *less;

        };

        struct Ibase {

            digit *most, *least;

        };

        Ibase _base;

        void zeroStrip( );


    public:

        LongInt();

        friend void printLongInt( LongInt );

        friend LongInt inputLongInt( );

        friend LongInt addLongInt( LongInt, LongInt );

};



void LongInt::zeroStrip( ){

    LongInt::digit * dptr = _base.most;

    LongInt::digit * extra = 0;

    while( ( !dptr->d_val ) && dptr->less ) {

        extra = dptr;

        _base.most = dptr->less;

        dptr = dptr->less;

        dptr->more = 0;

        delete extra;

    }

}



LongInt::LongInt(){

    _base.most = _base.least = new digit;

    _base.most->d_val = 0;

    _base.most->more = _base.most->less = 0;

};



void printLongInt( LongInt LIval ){

    LongInt::digit * dptr = LIval._base.most;

    while ( dptr ) {

        cout << dptr->d_val;

        dptr = dptr->less;

    }

}



LongInt inputLongInt( ){

    LongInt returnValue;

    int inValue;

    LongInt::digit * dptr = 0;

    LongInt::digit * inputList = 0;

    inputList = returnValue._base.least;

    inValue = cin.get();

    while ( '0' <= inValue && inValue <= '9' ){

        dptr = new LongInt::digit;

        dptr->d_val = inValue - '0';

        dptr->less = 0;

        dptr->more = inputList;

        returnValue._base.least = dptr;

        inputList->less = dptr;

        inputList = dptr;

        inValue = cin.get();

    }

    returnValue.zeroStrip( );

    return returnValue;

}



LongInt addLongInt(LongInt s1, LongInt s2) {

    LongInt::digit * cursor1 = s1._base.least;

    LongInt::digit * cursor2 = s2._base.least;


    int carry = 0;

    LongInt returnValue = LongInt();

    LongInt::digit * cursor3 = returnValue._base.least;


    while (cursor1 || cursor2) {

        int val1, val2 = 0;


        if (cursor1) {

            val1 = cursor1->d_val;

        }


        else {

            val1 = 0;

        }


        if (cursor2) {

            val2 = cursor2->d_val;

        }


        else {

            val2 = 0;

        }


        int sum = val1 + val2 + carry;

        carry = sum / 10;

        int remainder = sum % 10;


        cursor3->d_val = remainder;

        cursor3->more = new LongInt::digit();

        cursor3->more->d_val = carry;

        cursor3->more->less = cursor3;

        cursor3 = cursor3->more;

        returnValue._base.most = cursor3;


        if (cursor1) {

            cursor1 = cursor1->more;

        }


        else {

            cursor1 = 0;

        }


        if (cursor2) {

            cursor2 = cursor2->more;

        }


        else {

            cursor2 = 0;

        }

    }


    returnValue.zeroStrip();

    return returnValue;

}



int main(){

    LongInt summand1, summand2, sum;

    cout << "-> " << flush;

    summand1 = inputLongInt();

    cout << endl;


    cout << "-> " << flush;

    summand2 = inputLongInt();

    cout << endl;

    cout << "\n-----\n";


    sum = addLongInt( summand1, summand2 );

    printLongInt( sum );

    cout << endl;

}

