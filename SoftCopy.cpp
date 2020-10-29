#include "SoftCopy.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
THE CONSTRUCTOR and DESTRUCTOR ARE ALREADY IMPLEMENTED.
START YOUR IMPLEMENTATIONS BELOW THOSE. */


// DONE
SoftCopy::SoftCopy(int ISBN, double price, int startPage, int endPage) : Book(ISBN, price) {
	this->startPage = startPage;
	this->endPage = endPage;
	this->numberOfPages = (endPage - startPage) + 1;
	this->firstHalf = NULL;
	this->secondHalf = NULL;
	this->pageContent = "";
}

// DONE
SoftCopy::~SoftCopy() {
	if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;
}

SoftCopy::SoftCopy(const SoftCopy& rhs){
	ISBN = rhs.ISBN;
	price = rhs.price;
	next = rhs.next;
	startPage = rhs.startPage;
	endPage = rhs.endPage;
	numberOfPages = rhs.numberOfPages;
	pageContent = rhs.pageContent;
	if(rhs.firstHalf != NULL){
		firstHalf = new SoftCopy(*rhs.firstHalf);
	}
	else firstHalf = NULL;
	if(rhs.secondHalf != NULL){
		secondHalf = new SoftCopy(*rhs.secondHalf);
	}
	else secondHalf = NULL;
}

SoftCopy& SoftCopy::operator=(const SoftCopy& rhs){
	ISBN = rhs.ISBN;
	price = rhs.price;
	next = rhs.next;
	startPage = rhs.startPage;
	endPage = rhs.endPage;
	numberOfPages = rhs.numberOfPages;
	pageContent = rhs.pageContent;
	
	if(firstHalf!=NULL) delete firstHalf;
	if(secondHalf!=NULL) delete secondHalf;
	
	if(rhs.firstHalf != NULL){
		firstHalf = new SoftCopy(*rhs.firstHalf);
	}
	else firstHalf = NULL;
	if(rhs.secondHalf != NULL){
		secondHalf = new SoftCopy(*rhs.secondHalf);
	}
	else secondHalf = NULL;
	return *this;
}

void SoftCopy::Discount(){
	price = price*75/100;
	if(firstHalf) firstHalf->Discount();
	if(secondHalf) secondHalf->Discount();
}


Book* SoftCopy::Clone() const{
	SoftCopy* mycopy = new SoftCopy(*this);
	return mycopy;
}



SoftCopy& SoftCopy::operator+(const SoftCopy& rhs) const{
	vector<SoftCopy*> s;
    vector<SoftCopy*> asd;
    SoftCopy* mycopy = new SoftCopy(*this);
    SoftCopy* p = const_cast<SoftCopy *>(&rhs);
    while(p!=NULL || s.empty() == false){
        while(p != NULL){
            s.push_back(p);
            p = p->firstHalf;
        }
        p=s[0];
        s.erase(s.begin());
        if(p->numberOfPages==1) asd.push_back(p);
        p=p->secondHalf;
    }
    for(int i=0 ; i<asd.size(); i++){
        mycopy->UploadPage(asd[i]->pageContent, asd[i]->startPage);
    }
    s.clear();
    asd.clear();
    return *mycopy;
}


void SoftCopy::UploadPage(string s, int id){
	int lpn,lsp,lep,rpn,rsp,rep;
	rpn = numberOfPages/2;
	lpn = numberOfPages-rpn;
	rsp = endPage-rpn+1;
	rep = endPage;
	lsp = startPage;
	lep = lsp + lpn-1;

	if(numberOfPages==1 && endPage==id){
		pageContent = s;
	}

	else if(lsp <= id && lep >= id){
		if(firstHalf==NULL){
			firstHalf = new SoftCopy(ISBN, price, lsp, lep);
		}
		firstHalf->UploadPage(s, id);
	}

	else if(rsp <= id && rep >= id){
		if(secondHalf==NULL){
			secondHalf = new SoftCopy(ISBN, price, rsp, rep);
		}
		secondHalf->UploadPage(s, id);
	}
}


string SoftCopy::Display(int from, int to) const{
if(numberOfPages==1 && startPage >= from && endPage <= to){
	return pageContent;     
}
if(firstHalf!=NULL && secondHalf!=NULL){
	if (firstHalf->Display(from,to) == "" && secondHalf->Display(from,to) == "") return "";
	if (firstHalf->Display(from,to) == "") return secondHalf->Display(from,to);
	if (secondHalf->Display(from,to) == "") return firstHalf->Display(from,to);
	else return firstHalf->Display(from,to) + "\n" + secondHalf->Display(from,to); 
}
if(firstHalf!=NULL) return firstHalf->Display(from,to);
if(secondHalf!=NULL) return secondHalf->Display(from,to);

return "";
}