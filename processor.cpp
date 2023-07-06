#include <bits/stdc++.h>
// #include <conio.h>
#include <iostream>
#include <stdio.h>
#define ll long long int
#define fo(i, n) for (ll i = 0; i < n; i++)

using namespace std;
char PC[3] = "00", A[4] = "700", B[4] = "000", ALU = '0', IR[3] = "00", MAR[3] = "00", MDR[4] = "000", SP[3] = "FF", FLG = '0';
int carry = 0, zero = 0, int_flag = 0, intr_on = 0;
int i = 0;
char SI = '0', SO = '0', IN1[4] = "005", IN2[4] = "000", IN3[4] = "000", IN4[4] = "000", OUT1[4] = "000", OUT2[4] = "000", OUT3[4] = "000", OUT4[4] = "000";
int FGI1 = 0, FGI2 = 1, FGI3 = 1, FGI4 = 0, FGO1 = 0, FGO2 = 0, FGO3 = 0, FGO4 = 0;
char BS = '0';
char RAM[256][4];

void delay()
{
    for (int i = 0; i < 1e+9; i++)
        ;
}

void update_flag(int k, int &flag, int SR)
{
    if (SR == 1)
        flag = flag | (1 << k);
    else
        flag = flag & (~(1 << k));
}
int interrupt_take()
{
    // char ch;
    // while (_kbhit())
    // {
    // char ch = _getch();
    // if (ch == 'i')
    // {
    //     return 1;
    // }
    // }
    return 0;
}
void interrupt_print()
{
     cout << "......................Interrupt Handling...................." << endl;

    delay();
    cout << "." << endl
         << "." << endl
         << "." << endl
         << "." << endl
         << "." << endl
         << "." << endl
         << "." << endl
         << "." << endl;
    cout << "* * * * * * * *Interrupt has been serviced* * * * * * * *" << endl;
}
int hextodec(char ch)
{
    int a = ch - '0';
    int b = ch - '7';
    if (ch < 'A')
        return a;
    else
        return b;
}
int hex2dec(string s)
{
    int sum = 0;
    int m = 1;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        sum += hextodec(s[i]) * m;
        m = m * 16;
    }
    return sum;
}

string dec2hex(int n)
{
    if (n == 0)
    {
        return "0";
    }

    string ans = "";

    while (n != 0)
    {
        int rem = 0;

        char ch;

        rem = n % 16;

        if (rem < 10)
        {
            ch = rem + 48;
        }
        else
        {
            ch = rem + 55;
        }
        ans += ch;
        n = n / 16;
    }
    int i = 0, j = ans.size() - 1;
    while (i <= j)
    {
        swap(ans[i], ans[j]);
        i++;
        j--;
    }
    return ans;
}
void increment(char *PC)
{
    int temp = hex2dec(PC);
    temp++;
    string str = dec2hex(temp);
    if (str.size() == 1)
    {
        PC[1] = str[0];
    }
    else
    {
        PC[0] = str[0];
        PC[1] = str[1];
    }
}

void decrement(char *PC)
{
    int temp = hex2dec(PC);
    temp--;
    string str = dec2hex(temp);
    if (str.size() == 1)
    {
        PC[1] = str[0];
    }
    else
    {
        PC[0] = str[0];
        PC[1] = str[1];
    }
}

char Complement(char ch)
{
    unordered_map<char,char>mp;
    mp['0']='F';
    mp['1']='E';
    mp['2']='D';
    mp['3']='C';
    mp['4']='B';
    mp['5']='A';
    mp['6']='9';
    mp['7']='8';
    mp['8']='7';
    mp['9']='6';
    mp['A']='5';
    mp['B']='4';
    mp['C']='3';
    mp['D']='2';
    mp['E']='1';
    mp['F']='0';

return mp[ch];

}



void showContent()
{
    cout << endl;
    cout << "PC=" << PC[0] << PC[1] << " "
         << "IR=" << IR[0] << IR[1] << " "
         << "MDR=" << MDR[0] << MDR[1] << MDR[2] << " "
         << "MAR=" << MAR[0] << MAR[1] << " "
         << "SP=" << SP[0] << SP[1] << " "
         << "A=" << A[0] << A[1] << A[2] << " "
         << "B=" << B[0] << B[1] << B[2] << " " << endl 
         << "(ION=" << intr_on << " C=" << carry << " Z=" << zero << " R=" <<int_flag 
         << ") FLG=" << FLG << " "<<endl ;
    cout << "IN1=" << IN1[0] << IN1[1] << IN1[2] << " "
         << "IN2=" << IN2[0] << IN2[1] << IN2[2] << " "
         << "IN3=" << IN3[0] << IN3[1] << IN3[2] << " "
         << "IN4=" << IN4[0] << IN4[1] << IN4[2] << " -- " 
         << "FGI=" << FGI1 << FGI2 << FGI3 << FGI4 << " " <<endl
         << "OUT1=" << OUT1[0] << OUT1[1] << OUT1[2] << " "
         << "OUT2=" << OUT2[0] << OUT2[1] << OUT2[2] << " "
         << "OUT3=" << OUT3[0] << OUT3[1] << OUT3[2] << " "
         << "OUT4=" << OUT4[0] << OUT4[1] << OUT4[2] << " -- " 
         << "FGO=" << FGO1 << FGO2 << FGO3 << FGO4 <<endl;
    cout << endl;
}
void fetch()
{

    cout << "~Fetch:" << endl;
    cout << "T0 : PC(E) , MAR(E,L)" << endl;
    cout << "T1 : PC(I) , RAM(E) , MDR(L)" << endl;
    for (int j = 0; j < 2; j++)
    {
        MAR[j] = PC[j];
    }

    increment(PC);

    for (int j = 0; j < 3; j++)
    {
        MDR[j] = RAM[i][j];
    }

    showContent();
}

void decode()
{
    cout << "~Decode:" << endl;

    // For MRI instruction
    if (MDR[0] != '7' && MDR[0] != 'F')
    {
        cout << "This is MRI Instruction" << endl;

        IR[0] = '0';
        IR[1] = MDR[0];
        MAR[0] = MDR[1];
        MAR[1] = MDR[2];
        cout << "T2:  MDR(E) ,IR(L) , MAR(L,E)        // MAR <- MDR(7-0), IR <-MDR(8-11)" << endl;
    }

    // For Non MRI instruction
    else
    {
        cout << "This is non MRI Instruction" << endl;
        if (MDR[0] == 'F')
            IR[0] = '3';
        else
            IR[0] = '2';
        IR[1] = MDR[1];
        cout << "T2:  MDR(E) ,IR(L)         // IR <-MDR(4-7)" << endl;
    }

    showContent();
}

void solve(int n)
{

    i = 0;

    // Taking input in RAM

    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            cin >> RAM[j][k];
        }
    }

    // is while loop me interrupt ki condition bhi add krni padegi sayad
    while (!(RAM[i][1] == 'F' && RAM[i][0] == '7')) // Means HLT instruction jab tak nhi aa jata
    {

        fetch();
        decode();
        delay();
        
        int_flag = interrupt_take();
        int flag = hextodec(FLG);
        update_flag(0, flag, int_flag);
        string str = dec2hex(flag);
        FLG = str[0];
        
        cout << "~Execution:" << endl;

        // For MRI instruction

        if (!(RAM[i][0] == '7' || RAM[i][0] == 'F'))
        {
            switch (RAM[i][0])
            {

                // Direct LDA XX

            case '0':
            {
                cout<<endl;
                cout << " * * * * * * * * Direct LDA " << MAR[0] << MAR[1] << " * * * * * * * *" << endl;
                cout<<endl;
                int p = hex2dec(MAR);
                //  AC(L) , RAM(E), Reset
                for (int j = 0; j < 3; j++)
                {
                    A[j] = RAM[p][j];
                }

                //////////////Flag////////////////
                int a = hex2dec(A);
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];
                //////////////////////////////////////////////

                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:  AC(L) , RAM(E), Reset     // AC <- M[MAR]" << endl;
                showContent();
                break;
            }

                // Indirect LDA XX

            case '8':
            {
                cout<<endl;
                cout << " * * * * * * * * Indirect LDA " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
                int p = hex2dec(MAR);
                cout<<endl;
                // MDR(L) , RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }
                // MAR(L,E), MDR(E)
                for (int j = 0; j < 2; j++)
                {
                    MAR[j] = MDR[j + 1];
                }

                //  AC(L) , RAM(E), Reset
                int q = hex2dec(MAR);
                for (int j = 0; j < 3; j++)
                {
                    A[j] = RAM[q][j];
                }

                //////////////Flag////////////////
                int a = hex2dec(A);
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];
                //////////////////////////////////////////////

                cout << "T3:  MDR(L) , RAM(E)            // MDR <-M[MAR]" << endl;
                cout << "T4:  MAR(L,E), MDR(E)          // MAR <- MDR(7-0)" << endl;
                cout << "T5:  A(L) , RAM(E), Reset    // AC <- M[MAR]" << endl;
                showContent();
                break;
            }

            // Direct STA XX
            case '1':
            {
                cout<<endl;
                cout << " * * * * * * * * Direct STA " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
cout<<endl;
                int p = hex2dec(MAR);
                // RAM(L) , AC(E) , Reset
                for (int j = 0; j < 3; j++)
                {
                    RAM[p][j] = A[j];
                }
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:  RAM(L) , A(E), Reset" << endl<<endl;
                cout <<"Accumulaor Content--"<< A[0]<<A[1]<<A[2]<<" is loaded in Memory location "<<"0X"<<MDR[1]<<MDR[2]<<endl;
                showContent();
                break;
            }

            // Indirect STA XX
            case '9':
            {
                cout<<endl;
                cout << " * * * * * * * * Indirect STA " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
cout<<endl;
                int p = hex2dec(MAR);

                // MDR(L) , RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }
                // MAR(L,E), MDR(E)
                for (int j = 0; j < 2; j++)
                {
                    MAR[j] = MDR[j + 1];
                }

                // RAM(L) , AC(E) , Reset
                int q = hex2dec(MAR);
                for (int j = 0; j < 3; j++)
                {
                    RAM[q][j] = A[j];
                }
                cout << "T3:  MDR(L) , RAM(E)" << endl;
                cout << "T4:  MAR(L,E), MDR(E)" << endl;
                cout << "T5:  RAM(L) , A(E), Reset" << endl;
                cout <<"Accumulaor Content--"<< A[0]<<A[1]<<A[2]<<" is loaded in Memory location "<<"0X"<<MAR[0]<<MAR[1]<<endl;
                showContent();
                break;
            }

                // Direct ADM XX------------------------Zero and Carry Flag Changes
            case '2':
            {
                cout<<endl;
                cout << " * * * * * * * * Direct ADM " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
cout<<endl;
                int p = hex2dec(MAR);

                // MDR(L) , RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }
                // AC <-AC + MDR
                for (int j = 0; j < 3; j++)
                {
                    A[j] = A[j] + MDR[j];
                }

                //////////////Flag////////////////
                int a = hex2dec(A);
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];

                ////////////////Carry/////////////////////
                if (a > 4095)
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
                flag = hextodec(FLG);
                update_flag(2, flag, carry);
                st = dec2hex(flag);
                FLG = st[0];
                //////////////////////////////////////////////

                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:  MDR(L) , RAM(E), Reset" << endl;
                cout << "T6:A <- A + MDR,Reset" << endl;
                showContent();
                break;
            }

            // Indirect ADM XX------------------------Zero and Carry Flag Changes
            case 'A':
            {
                cout << " * * * * * * * * Indirect ADM " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
                int p = hex2dec(MAR);
cout<<endl;
                // MDR(L) , RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }
                // MAR(L,E),MDR(E)
                for (int j = 0; j < 2; j++)
                {
                    MAR[j] = MDR[j + 1];
                }
                int q = hex2dec(MAR);

                // MDR(L) , RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[q][j];
                }
                // AC <-AC + MDR
                for (int j = 0; j < 3; j++)
                {
                    A[j] = A[j] + MDR[j];
                }

                //////////////Flag////////////////
                int a = hex2dec(A);
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];

                ////////////////Carry/////////////////////
                if (a > 4095)
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
                flag = hextodec(FLG);
                update_flag(2, flag, carry);
                st = dec2hex(flag);
                FLG = st[0];
                //////////////////////////////////////////////

                cout << "T3:  MDR(L) , RAM(E)" << endl;
                cout << "T4:  MAR(L,E), MDR(E)" << endl;
                cout << "T5:  MDR(L) , RAM(E)" << endl;
                cout << "T6: A <- A + MDR,Reset" << endl;
                showContent();
                break;
            }

                // Direct CALL XX
            case '3':
            {
                cout<<endl;
                cout << " * * * * * * * * Direct CALL " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
                //  SP(D)
cout<<endl;
                decrement(SP);

                // SP(E), MAR(E,L)
                for (int j = 0; j < 2; j++)
                {
                    MAR[j] = SP[j];
                }
                // RAM(L), PC(E)

                int p = hex2dec(MAR);
                for (int j = 0; j < 2; j++)
                {
                    RAM[p][j + 1] = PC[j];
                }

                // PC(L), MDR(E), Reset
                for (int j = 0; j < 2; j++)
                {
                    PC[j] = MDR[j + 1];
                }

                i=hex2dec(PC)-1;

                cout << "T3:  Idle" << endl;
                cout << "T4:  Idle" << endl;
                cout << "T5: SP(D)" << endl;
                cout << "T6: SP(E), MAR(E,L)" << endl;
                cout << "T7:  RAM(L), PC(E)" << endl;
                cout << "T8: PC(L),MDR(E), RESET" << endl;
                showContent();
                break;
            }

            // Indirect CALL XX
            case 'B':
            {
                cout<<endl;
                cout << " * * * * * * * * Indirect CALL " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
cout<<endl;
                int p = hex2dec(MAR);

                // MDR(L) , RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }

                //  SP(D)

                decrement(SP);

                // SP(E), MAR(E,L)
                for (int j = 0; j < 2; j++)
                {
                    MAR[j] = SP[j];
                }
                // RAM(L), PC(E)
                int q = hex2dec(MAR);
                for (int j = 0; j < 2; j++)
                {
                    RAM[q][j + 1] = PC[j];
                }
                // PC(L), MDR(E), Reset
                for (int j = 0; j < 2; j++)
                {
                    PC[j] = MDR[j + 1];
                }

                i=hex2dec(PC)-1;
                cout << "T4:  Idle" << endl;
                cout << "T5: SP(D)" << endl;
                cout << "T6: SP(E), MAR(E,L)" << endl;
                cout << "T7:  RAM(L), PC(E)" << endl;
                cout << "T8: PC(L),MDR(E)" << endl;
                showContent();
                break;
            }

                // Direct JMP XX
            case '4':
            {
                cout<<endl;
                cout << " * * * * * * * * Direct JMP " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
                cout<<endl;
                // PC(L), MDR(E), Reset
                for (int j = 0; j < 2; j++)
                {
                    PC[j] = MDR[j + 1];
                }
                i=hex2dec(PC)-1;
                cout << "T3:  Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5: PC(L),MDR(E), Reset" << endl;
                showContent();
                break;
            }

            // Indirect JMP XX
            case 'C':
            {
                cout<<endl;
                cout << " * * * * * * * * Indirect JMP " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
                int p = hex2dec(MAR);
cout<<endl;
                // MDR(L), RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }
                // PC(L), MDR(E), Reset
                for (int j = 0; j < 2; j++)
                {
                    PC[j] = MDR[j + 1];
                }
                i=hex2dec(PC)-1;
                cout << "T4: Idle" << endl;
                cout << "T5: PC(L),MDR(E), Reset" << endl;
                showContent();
                break;
            }

            // Direct JC XX
            case '5':
            {
                cout<<endl;
                cout << " * * * * * * * * Direct JC " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;

cout<<endl;
                int fl = hextodec(FLG);
                if ((fl & 4))
                {
                    // PC(L), MDR(E), Reset
                    for (int j = 0; j < 2; j++)
                    {
                        PC[j] = MDR[j + 1];
                    }
                    i=hex2dec(PC)-1;
                }
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5: PC(L),MDR(E), Reset" << endl;
                showContent();
                break;
            }

            // Indirect JC XX
            case 'D':
            {
                cout<<endl;
                cout << " * * * * * * * * Indirect JC " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
cout<<endl;
                int p = hex2dec(MAR);

                // MDR(L), RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }
                int fl = hextodec(FLG);
                if ((fl & 4))
                {
                    // PC(L), MDR(E), Reset
                    for (int j = 0; j < 2; j++)
                    {
                        PC[j] = MDR[j + 1];

                    }
                    i=hex2dec(PC)-1;
                }
                cout << "T4: Idle" << endl;
                cout << "T5: PC(L),MDR(E), Reset" << endl;
                showContent();
                break;
            }
            // Direct JZ XX
            case '6':
            {
                cout<<endl;
                cout << " * * * * * * * * Direct JZ " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
                cout<<endl;
                int fl = hextodec(FLG);
                if ((fl & 2))
                {
                    // PC(L), MDR(E), Reset
                    for (int j = 0; j < 2; j++)
                    {
                        PC[j] = MDR[j + 1];
                    }
                    i=hex2dec(PC)-1;
                }
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5: PC(L),MDR(E), Reset" << endl;
                showContent();
                break;
            }

            // Indirect JZ XX
            case 'E':
            {
                cout<<endl;
                cout << " * * * * * * * * Indirect JZ " << MAR[0] << MAR[1] << " * * * * * * * * " << endl;
                
cout<<endl;
                int p = hex2dec(MAR);

                // MDR(L), RAM(E)
                for (int j = 0; j < 3; j++)
                {
                    MDR[j] = RAM[p][j];
                }
                int fl = hextodec(FLG);
                if ((fl & 2))
                {
                    // PC(L), MDR(E), Reset
                    for (int j = 0; j < 2; j++)
                    {
                        PC[j] = MDR[j + 1];
                    }
                    i=hex2dec(PC)-1;
                }
                cout << "T4: Idle" << endl;
                cout << "T5: PC(L),MDR(E), Reset" << endl;
                showContent();
                break;
            }
            default:
                cout << endl <<"Enter a valid instruction"<<endl<<endl;
                break;
            }
        }

        // for non MRI instruction
        else if (RAM[i][0] == '7')
        {

            switch (RAM[i][1])
            {

                // ADD B------------------------Zero Flag Changes
            case '0':
            {
                cout<<endl;
                cout << "* * * * * * * * ADD B * * * * * * * * " << endl;
                
cout<<endl;
                int a = hex2dec(A);
                int b = hex2dec(B);
                a = a + b;

                if (a > 4095)
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
                if (a == 0 || (a - 4096) == 0)
                {
                    zero = 1;
                }
                else
                {
                    zero = 0;
                }
                int flag = hextodec(FLG);
                update_flag(2, flag, carry);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];

                string temp = dec2hex(a);
                if (temp.size() <= 3)
                {
                    int n = 3 - temp.size();

                    for (int i = 0; i < n; i++)
                    {
                        A[i] = '0';
                    }
                    for (int i = n; i < 3; i++)
                    {
                        A[i] = temp[i - n];
                    }
                }

                else
                {
                    for (int i = temp.size() - 3; i < temp.size(); i++)
                    {
                        A[i - (temp.size() - 3)] = temp[i];
                    }
                }
                ALU = '0';
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:  A(E,L) , B(E) , ALU(000) , Reset" << endl;
                showContent();
                break;
            }

                // SUB B------------------------Zero Flag Changes
            case '1':
            {
                cout<<endl;
                cout << "* * * * * * * * SUB B * * * * * * * * " << endl;
                
cout<<endl;
                int a = hex2dec(A);
                int b = hex2dec(B);
                a = a - b;

                ////FLag //////////////
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;
                if (a < 0)
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
                int flag = hextodec(FLG);
                update_flag(2, flag, carry);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];
                //////////////////////////

                string temp = dec2hex(a);
                string str;

                if (temp.size() < 3)
                {
                    int n = 3 - temp.size();

                    for (int i = 0; i < n; i++)
                    {
                        str[i] = '0';
                    }
                    for (int i = n; i < 3; i++)
                    {
                        str[i] = temp[i - n];
                    }
                }
                for (int i = 0; i < 3; i++)
                {
                    A[i] = str[i];
                }
                ALU = '1';
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:  A(E,L) , B(E) , ALU(001) , Reset" << endl;
                showContent();
                break;
            }

                // CLA   ------------------------Zero  Flag Changes

            case '2':
            {
                cout<<endl;
                cout << "* * * * * * * * CLA * * * * * * * * " << endl;
                cout<<endl;


                for (int i = 0; i < 3; i++)
                {
                    A[i] = '0';
                }
                //////////Flag//////////////
                zero = 1;
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];
                ////////////////////////////

                ALU = '2';
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:  A(E,L) , ALU(002) , Reset" << endl;
                showContent();
                break;
            }

                // CMA  ------------------------Zero  Flag Changes
            case '3':
            {
                cout<<endl;
                cout << "* * * * * * * * CMA * * * * * * * * " << endl;
cout<<endl;

                   for(int i=0;i<3;i++){
                      A[i]= Complement(A[i]);
                     }
                


             
                ////////Flag///////////////
                int a = hex2dec(A);
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                string st = dec2hex(flag);
                FLG = st[0];
                ///////////////////////////////

                string temp = dec2hex(a);
                string str;
                if (temp.size() < 3)
                {
                    int n = 3 - temp.size();

                    for (int i = 0; i < n; i++)
                    {
                        str[i] = '0';
                    }
                    for (int i = n; i < 3; i++)
                    {
                        str[i] = temp[i - n];
                    }
                }
                for (int i = 0; i < 3; i++)
                {
                    A[i] = str[i];
                }
                ALU = '3';
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:  A(E,L) , ALU(003) , Reset" << endl;
                showContent();
                break;
            }

                // MOV A,B
            case '4':
            {
                cout<<endl;
                cout << "* * * * * * * * MOV A,B * * * * * * * * " << endl;
                cout<<endl;
                for (int i = 0; i < 3; i++)
                {
                    A[i] = B[i];
                }

                ALU = '4';
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:   B(E) , A(L) , Reset" << endl;
                showContent();
                break;
            }

                // MOV B,A

            case '5':
            {
                cout<<endl;
                cout << "* * * * * * * * MOV B,A * * * * * * * * " << endl;
                cout<<endl;
                for (int i = 0; i < 3; i++)
                {
                    B[i] = A[i];
                }
                ALU = '5';
                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5:   B(L) , A(E) , Reset" << endl;
                showContent();
                break;
            }

                // PUSH
            case '6':
            {
                cout<<endl;
                cout << "* * * * * * * * PUSH A * * * * * * * * " << endl;
                cout<<endl;
                // SP(D)
                // FF FE
                decrement(SP);
                // SP(E) , MAR(E,L)

                for (int j = 0; j < 2; j++)
                {
                    MAR[j] = SP[j];
                }

                // RAM(L) , A(E) , Reset

                int stackpointer = hex2dec(MAR);

                for (int j = 0; j < 3; j++)
                {
                    RAM[stackpointer][j] = A[j];
                }

                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5: SP(D)" << endl;
                cout << "T6: SP(E) MAR(E,L)" << endl;
                cout << "T7: RAM(L) , A(E) , Reset" << endl;
                showContent();
                break;
            }

                // POP

            case '7':
            {
                cout<<endl;
                cout << "* * * * * * * * POP * * * * * * * * " << endl;
                cout<<endl;

                if(SP[0]=='F' && SP[1]=='F')
                {
                    cout<<"Stack is Empty cannot POP"<<endl;
                }
                // SP(E) , MAR(E,L)

                else
                {
                    for (int j = 0; j < 2; j++)
                    {
                        MAR[j] = SP[j];
                    }

                    // RAM(E) , A(L) , Reset

                    int stackpointer = hex2dec(MAR);

                    for (int j = 0; j < 3; j++)
                    {
                        A[j] = RAM[stackpointer][j];
                    }

                    // SP(I)

                    increment(SP);
                

                    cout << "T3: Idle" << endl;
                    cout << "T4: Idle" << endl;
                    cout << "T5: SP(E) ,MAR(E,L)" << endl;
                    cout << "T6: RAM(E) , A(L) " << endl;
                    cout << "T7: SP(I) ,RESET" << endl;
                }
                showContent();
                break;
            }

                // RET

            case '8':
            {
                cout<<endl;
                cout << "* * * * * * * * RET * * * * * * * * " << endl;
                cout<<endl;
                // SP(E) , MAR(E,L)
                if(SP[0]=='F' && SP[1]=='F')
                {
                    cout<<"Stack is Empty "<<endl;
                }
                else{
                for (int j = 0; j < 2; j++)
                {
                    MAR[j] = SP[j];
                }

                // RAM(E) , PC(L) , Reset

                int stackpointer = hex2dec(MAR);

                for (int j = 0; j < 2; j++)
                {
                    PC[j] = RAM[stackpointer][j+1];
                }

                // SP(I)

                increment(SP);
                i=hex2dec(PC)-1;

                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5: SP(E) ,MAR(E,L)" << endl;
                cout << "T6: RAM(E) , PC(L) " << endl;
                cout << "T7: SP(I) ,RESET" << endl;

            }
                showContent();
                break;
            }

                // MVI A,data

            case '9':
            {
                cout<<endl;
                cout << "* * * * * * * * MVI A," << MDR[2] << " * * * * * * * * " << endl;
                
cout<<endl;
                // MDR(E), A(L) , Reset        // A <- MDR(0-3)

                A[2] = MDR[2];
                A[0] = '0';
                A[1] = '0';

                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5: MDR(E) ,A(L), RESET" << endl;
                showContent();
                break;
            }

                // MVI F,data

            case 'A':
            {
                cout<<endl;
                cout << "* * * * * * * * MVI FLG," << MDR[2] << " * * * * * * * * " << endl;
                
cout<<endl;
                // MDR(E), F(L) , Reset        // F <- MDR(0-3)

                FLG = MDR[2];
                int temp = hextodec(FLG);

                intr_on = temp & 8;
                intr_on = intr_on >> 3;
                zero = temp & 2;
                zero = zero >> 1;
                carry = temp & 4;
                carry = carry >> 2;
                int_flag = temp & 1;

                cout << "T3: Idle" << endl;
                cout << "T4: Idle" << endl;
                cout << "T5: MDR(E) ,F(L), RESET" << endl;
                showContent();
                break;
            }
            case 'B': //------------------------Carry  Flag Changes
            {
                cout<<endl;
                cout << "* * * * * * * * LSC A," << MDR[2] << " * * * * * * * * " << endl;
cout<<"T6:   A(E,L), BS(E), Reset"<<endl;
                //    MDR(E), BS(L)
                BS = MDR[2];

                int bsi = hextodec(BS);

                // A(E,L), BS(E), Reset

                int a = hex2dec(A);
                
                carry = a & 1<<(12-bsi);
                if(carry>0)
                    carry=1;

                
               
                a = a << bsi;

                /////////////////////Flag///////////////
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;

               
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                update_flag(2, flag, carry);
                string st = dec2hex(flag);
                FLG = st[0];
                ////////////////////////////////////////

                string temp = dec2hex(a);


                // Padding if size is less than 3
                if (temp.size() <= 3)
                {
                    int n = 3 - temp.size();

                    for (int i = 0; i < n; i++)
                    {
                        A[i] = '0';
                    }
                    for (int i = n; i < 3; i++)
                    {
                        A[i] = temp[i - n];
                    }
                }

                else
                {
                    for (int i = temp.size() - 3; i < temp.size(); i++)
                    {
                        A[i - (temp.size() - 3)] = temp[i];
                    }
                }
                
                // string str;
                // str = dec2hex(a);
                // int c = 3;
                // int j = 0;
                // while (c--)
                // {
                //     A[2 - j] = str[str.size() - 1 - j];
                //     j++;
                // }

                showContent();
                
                break;
            }

            case 'C': //------------------------Carry  Flag Changes
            {
                cout<<endl;
                cout << "* * * * * * * * RSC A," << MDR[2] << " * * * * * * * * " << endl;
                
cout<<"T6:   A(E,L), BS(E), Reset"<<endl;
                //    MDR(E), BS(L)
                BS = MDR[2];

                int bsi = hextodec(BS);

                // A(E,L), BS(E), Reset

                int a = hex2dec(A);

                carry = a & (1<<(bsi-1));
                if(carry>0)
                    carry=1;

                // cout<<carry<<endl;

                a = a >> bsi;

                string temp = dec2hex(a);


                // Padding if size is less than 3
                if (temp.size() <= 3)
                {
                    int n = 3 - temp.size();

                    for (int i = 0; i < n; i++)
                    {
                        A[i] = '0';
                    }
                    for (int i = n; i < 3; i++)
                    {
                        A[i] = temp[i - n];
                    }
                }

                else
                {
                    for (int i = temp.size() - 3; i < temp.size(); i++)
                    {
                        A[i - (temp.size() - 3)] = temp[i];
                    }
                }
                
                //////////////Carry Flag////////////////
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;

                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                update_flag(2, flag, carry);
                string st = dec2hex(flag);
                FLG = st[0];

                //////////////////////////////////////////////

                showContent();
                
                break;
            }


            case 'D': //------------------------Carry  Flag Changes
            {
                cout<<endl;
                cout << "* * * * * * * * RRC A," << MDR[2] << " * * * * * * * * " << endl;
                
cout<<"T6:   A(E,L), BS(E), Reset"<<endl;
                //    MDR(E), BS(L)
                BS = MDR[2];

                int bsi = hextodec(BS);

                // A(E,L), BS(E), Reset

                int a = hex2dec(A);

                carry = a & (1<<(bsi-1));
                if(carry>0)
                    carry=1;


                while (bsi--)
                {
                    if (a & 1)
                    {
                        a = a >> 1;
                        a += 2048;
                    }
                    else
                    {
                        a = a >> 1;
                    }
                }

                string str = dec2hex(a);
                for (int j = 0; j < 3; j++)
                {
                    A[j] = str[j];
                }

                //////////////Flag////////////////

                a = hex2dec(A);
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;
                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                update_flag(2, flag, carry);
                string st = dec2hex(flag);
                FLG = st[0];

                //////////////////////////////////////////////

                showContent();
                break;
            }
            case 'E':
            {
                cout<<endl;
                cout << "* * * * * * * * ASC A," << MDR[2] << " * * * * * * * * " << endl;
                
                BS = MDR[2];

                int bsi = hextodec(BS);

                // A(E,L), BS(E), Reset

                int a = hex2dec(A);

                carry = a & (1<<(bsi-1));
                if(carry>0)
                    carry=1;


                while (bsi--)
                {
                    if (a & (1<<11))
                    {
                        a = a >> 1;
                        a += 2048;
                    }
                    else
                    {
                        a = a >> 1;
                    }
                }

                string temp = dec2hex(a);

                // Padding if size is less than 3
                if (temp.size() <= 3)
                {
                    int n = 3 - temp.size();

                    for (int i = 0; i < n; i++)
                    {
                        A[i] = '0';
                    }
                    for (int i = n; i < 3; i++)
                    {
                        A[i] = temp[i - n];
                    }
                }

                else
                {
                    for (int i = temp.size() - 3; i < temp.size(); i++)
                    {
                        A[i - (temp.size() - 3)] = temp[i];
                    }
                }

                //////////////Flag////////////////

                a = hex2dec(A);
                if (a == 0)
                    zero = 1;
                else
                    zero = 0;

                int flag = hextodec(FLG);
                update_flag(1, flag, zero);
                update_flag(2, flag, carry);
                string st = dec2hex(flag);
                FLG = st[0];

                //////////////////////////////////////////////

                showContent();


                cout<<"T6:   A(E,L), BS(E), Reset"<<endl;
                break;
            }
            default:
            {
                cout << endl <<"Enter a valid instruction"<<endl<<endl;

                break;
            }
            }
        }
        else if (RAM[i][0] == 'F')
        {
            switch (RAM[i][1])
            {
                // IN
            case '0':
            {
                cout<<endl;
                cout << "* * * * * * * * IN " << MDR[2] << " * * * * * * * * " << endl;
                cout<<"T6:   A(L), IN(E), FGI(0) , Reset"<<endl;
                SI = MDR[2];
                int si_dec = hextodec(SI);
                if (si_dec & 1)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        A[k] = IN1[k];
                        FGI1=0;
                    }
                    // A=IN1;
                }
                else if (si_dec & 2)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        A[k] = IN2[k];
                        FGI2=0;
                    }
                }
                else if (si_dec & 4)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        A[k] = IN3[k];
                        FGI3=0;
                    }
                }
                else if (si_dec & 8)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        A[k] = IN4[k];
                        FGI4=0;
                    }
                }
                showContent();
                

                break;
            }

                // OUT
            case '1':
            {
                cout<<endl;
                cout << "* * * * * * * * OUT " << MDR[2] << " * * * * * * * * " << endl;
                cout<<"T6:   A(E), OUT(L), FGO(0), Reset"<<endl;
                SO = MDR[2];
                int so_dec = hextodec(SO);
                if (so_dec & 1)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        OUT1[k] = A[k];
                        FGO1=0;
                    }
                    // A=IN1;
                }
                else if (so_dec & 2)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        OUT2[k] = A[k];
                        FGO2=0;
                    }
                }
                else if (so_dec & 4)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        OUT3[k] = A[k];
                        FGO3=0;
                    }
                }
                else if (so_dec & 8)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        OUT4[k] = A[k];
                        FGO4=0;
                    }
                }
                showContent();
                break;
            }

            case '2':
            {
                cout<<endl;
                cout << "* * * * * * * * SKI " << MDR[2] << " * * * * * * * * " << endl;
                cout<<endl;
                //                     T5:  MDR(E), SI(L)           // SI <- MDR(0-3)
                // T6:   PC(I), Reset           // if FGI=1,PC<-PC+1, ( FGI is selected by SI )
                //    else Reset
                cout<<"T6: ";
                SI = MDR[2];
                int si_dec = hextodec(SI);
                if (si_dec & 1)
                {
                    if (FGI1 == 1)
                    {
                       increment(PC);
                       cout<<"  PC(I), ";
                    }
                    // A=IN1;
                }
                else if (si_dec & 2)
                {
                    if (FGI2 == 1)
                    {
                        increment(PC);
                        cout<<"  PC(I), ";
                    }
                }
                else if (si_dec & 4)
                {
                    if (FGI3 == 1)
                    {
                        increment(PC);
                        cout<<"  PC(I), ";
                    }
                }
                else if (si_dec & 8)
                {
                    if (FGI4 == 1)
                    {
                        increment(PC);
                        cout<<"  PC(I), ";
                    }

                }
                cout<<"Reset"<<endl;
                i=hex2dec(PC)-1;
                showContent();
                break;
            }

            case '3':
            {
                cout<<endl;
                cout << "* * * * * * * * SKO " << MDR[2] << " * * * * * * * * " << endl;
                cout<<endl;
                SO = MDR[2];
                int so_dec = hextodec(SO);
                cout<<"T6: ";
                if (so_dec & 1)
                {
                    if (FGO1 == 1)
                    {
                        increment(PC);
                        cout<<"  PC(I), ";
                    }
                }
                else if (so_dec & 2)
                {
                    if (FGO2 == 1)
                    {
                       increment(PC);
                       cout<<"  PC(I), ";
                        
                    }
                }
                else if (so_dec & 4)
                {
                    if (FGO3 == 1)
                    {
                        increment(PC);
                        cout<<"  PC(I), ";
                    }
                }
                else if (so_dec & 8)
                {
                    if (FGO4 == 1)
                    {
                        increment(PC);
                        cout<<"  PC(I), ";
                    }
                }
                cout<<"Reset"<<endl;
                i=hex2dec(PC)-1;
                showContent();
                break;
            }
            default:
            {
                cout << endl <<"Enter a valid instruction"<<endl<<endl;

                break;
            }
            }

           
        }
         if (intr_on == 0) // 0 - processor will be handling interrupt
                              // 1 - processor will not be handling interrupt
            {
                if (int_flag == 1) // pressed i for interrupt
                {
                    decrement(SP);
                    MAR[0] = SP[0];
                    MAR[1] = SP[1];

                    int p = hex2dec(MAR);
                    for (int j = 0; j < 2; j++)
                    {
                        RAM[p][j + 1] = PC[j];
                    }
                    PC[1] = '0';
                    PC[0] = 'F';
                    cout<<"* * * * * * * *Interrupt Has Occured* * * * * * * *"<<endl;
                    cout << " PC jump to location 0xF0 where Interrupt handling subroutine is written and Stack has the return address and R flag is set." << endl;
                    showContent();

                    interrupt_print();

                    increment(PC);
                    int_flag = 0;
                    int flag = hextodec(FLG);
                    update_flag(0, flag, int_flag);

                    string str = dec2hex(flag);
                    FLG = str[0];

                    // R flag reset
                    showContent();
                    cout<<"* * * * * * * *PC will jump to main program where the interrupt has occured* * * * * * * *"<<endl;
                    // At location F1, RET instruction is stored where PC <- SP
                    for (int j = 0; j < 2; j++)
                    {
                        PC[j] = RAM[p][j + 1];
                    }
                    increment(SP);
                    showContent();
                }
            }
        //cout << "- Registers Updated -" <<endl<<endl;
        cout << endl<<"--- NEXT INSTRUCTION ---" <<endl<<endl;
        i++;
    }

    if (RAM[i][0] == '7' && RAM[i][1] == 'F')
    {
        fetch();
        decode();
        cout << " * * * * * * * * HALT has occured * * * * * * * * " << endl;
        showContent();
    }
}

int main()
{
     // ios_base::sync_with_stdio(0), cin.tie(0), coutv.tie(0);
     #ifndef ONLINE_JUDGE
         // for getting input
        freopen("input.txt","r",stdin);
       // for writing output
        freopen("output.txt","w",stdout);
     #endif
    int n;
    cout << "no of instructions:" << endl;
    cin >> n;
    solve(n);

    return 0;
}
