#include <iostream>
using namespace std;

struct Node
{
    int power;
    int coeff;
    Node* next;
};

void printList(Node* head)
/*
* Prints a polynomial
*/
{
    // traverses a polynomial and prints each term, 
    // term by term
    while (head != NULL)
    {
        if (head->coeff != 0)
        {
            if (head->power == 0)
                cout << head->coeff;
            else
                cout << head->coeff << "x^" << head->power;

            if(head->next != NULL)
                cout << " + ";
        }
        head = head->next;       
    }
    cout <<endl;
}

Node* populate(int c, int p, Node* first)
/*
* Populates a polynomial with coefficient c and exponent p, term by term 
*/
{
    Node* poly = new Node, * orig = new Node;
    // populates new node with the coefficient and exponent passed
    poly->coeff = c;
    poly->power = p;
    poly->next = NULL;
    
    // if this is the first call with a new polynomial, 
    // then poly is returned as the first term
    if (first == NULL)
        return poly;

    // creates temperary lists so to not poison the polynomial passed
    Node* prime = orig = first;
          
    // traverses the polynomial passed until the second to last node is reached
    while (prime->next != NULL)
        prime = prime->next;
    // last node is assigned to be the new node created earlier
    prime->next = poly;

    return orig;
}

Node* polyAdd(Node* P,Node* Q, Node* R)
/* 
* Adds two polynomials together
*/
{
    Node* temp = new Node;
    temp = R;
    // traverses P and Q, adding terms with like exponents 
    // and adding them to R. Also adds terms to R that 
    // do not have like exponents
    while (P->next != NULL && Q->next != NULL)
    {
        // if the exponent of P is > than the exponent of Q, 
        // then the P term is added to R
        if (P->power > Q->power)
        {
            R->power = P->power;
            R->coeff = P->coeff;            
            P = P->next;
        }

        // if the exponent of P is < the exponent of Q, 
        // then the Q term is added to R
        else if (P->power < Q->power)
        {
            R->power = Q->power;
            R->coeff = Q->coeff;
            Q = Q->next;
        }
    
        // if the exponents of P and Q are equal,
        // then the coefficients are added together and
        // then added to R
        else if(P->power == Q->power)
        {
            R->power = P->power;
            R->coeff = P->coeff + Q->coeff;
            P = P->next;
            Q = Q->next;
        }

        // primes R for the next term to be added
        R->next = new Node;
        R = R->next;
        R->next = NULL;

        
    }
    // this handles the cases near the end of the polynomial
    // where one polynomial is longer than another. This also
    // adds the constants together and adds it to R
    while (P->next != NULL || Q->next != NULL)
    {
        // if P is not fully traversed, then the next term is
        // added to R
        if (P->next != NULL)
        {
            R->power = P->power;
            R->coeff = P->coeff;
            P = P->next;
        }
        // if Q is not fully traversed, then the next term is
        // added to R
        if (Q->next != NULL)
        {
            R->power = Q->power;
            R->coeff = Q->coeff;
            Q = Q->next;
        }
      
        // primes R for the next term to be added
        R->next = new Node;
        R = R->next;
        R->next = NULL; 

      
        // adds the constants together and adds it to the end of R
        if (P->power == 0 && Q->power == 0)
        {
            R->power = P->power;
            R->coeff = P->coeff + Q->coeff;
            break;
        } 
        // primes R for the next term to be added
        R->next = new Node;
        R = R->next;
        R->next = NULL;
    } 
    return temp;
}
Node* depend(Node* head)
/* 
* Adds 0 to the end of a polynomial if a constant does not already exist
*/
{
    // creates temperary lists so to not poison the polynomial passed
    Node* temp = head, * orig = head;

    // traverses through the polynomial and adds a 0 to the polynomial
    // if a constant does not exist
    while (head != NULL)
    {
        if (head->next == NULL)
        {
            if (head->power != 0) 
            {
                temp = populate(0, 0, temp);
                return temp;
            }
        }
        head = head->next;
    }
    // if the polynomial has a constant, then nothing is changed
    return orig;
}

Node* userInput(Node* head) 
{
    cout << "*type -1 on next prompt for coefficient and exponent to move on" << endl;
    while (true)
    {
        int coeff, power;
        cout << "enter the coefficient and exponent for this "
            << "term for polynomial in the form: coefficient exponent ";

        cin >> coeff >> power;

        if (coeff == -1)
            break;

        head = populate(coeff, power, head);
    }
    return head;
}

int main()
{
    // create polynomials P and Q
    Node* P = NULL,* Q = NULL;   

    // gets values for each polynomial
    P = userInput(P);
    Q = userInput(Q);

    // prints P and Q
    printList(P);
    printList(Q);
        
    // creates polynomial R
    Node* R = NULL;
    R = new Node;

    // adds P and Q together to make R
    R = polyAdd(depend(P), depend(Q), R);
    // prints R
    printList(R);
}
