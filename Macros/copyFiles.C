// Author: Rene Brun

#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"

  //Example of script showing how to copy all objects (including directories)
  //from a source file.
  //For each input file, a new directory is created in the current directory 
  //with the name of the source file.
  //After execution of:
  // root > .x copyFiles.C
  //the file result.root will contain 4 subdirectories:
  // "tot100.root", "hsimple.root", "hs1.root","hs2.root"
      
void CopyDir(TDirectory *source, Int_t option=1){
   //copy all objects and subdirs of directory source as a subdir of the current directory   
   source->ls();
   TDirectory *savdir = gDirectory;
   TDirectory *adir;
   if(option){
     adir = savdir->mkdir(source->GetName());
     adir->cd();
   }else{
     adir = savdir;
     adir->cd();
   }

   std::cout << "check " <<  source->GetName() << std::endl;

   //loop on all entries of this directory
   TKey *key;
   TIter nextkey(source->GetListOfKeys());
   while ((key = (TKey*)nextkey())) {
      const char *classname = key->GetClassName();
      TClass *cl = gROOT->GetClass(classname);
      if (!cl) continue;
      if (cl->InheritsFrom(TDirectory::Class())) {

	std::cout << "key : "  << key->GetName() << std::endl;
         source->cd(key->GetName());
         TDirectory *subdir = gDirectory;
         adir->cd();
         CopyDir(subdir);
         adir->cd();
      }else {
         source->cd();

	 std::cout << "object : "  << key->GetName() << std::endl;

         TObject *obj = key->ReadObj();
         adir->cd();

	 TH1F *hh = (TH1F*) obj;
	 //	 std::cout << "It is the modification time !---" << key->GetName() << "---" << source->GetName() << "---"<< std::endl;
	 TString htype = key->GetName();
	 TString stype = source->GetName();

	 if(htype=="W" && stype=="muTau_vbf_tight"){ 

	   Float_t orig = hh->GetSumOfWeights();
	   for(int ii=1; ii < hh->GetXaxis()->GetNbins()+1; ii++){
	     std::cout << ii  << " " << hh->GetBinCenter(ii) << " " << hh->GetBinContent(ii) << std::endl;
	     if(ii==5 && hh->GetBinCenter(ii)==90){
	       Float_t val = (hh->GetBinContent(ii-1) + hh->GetBinContent(ii+1))/2.;
	       Float_t err = hh->GetBinError(ii)*(val/hh->GetBinContent(ii));
	       std::cout << "original_err, ratio, new = " << hh->GetBinError(ii) << " " << (val/hh->GetBinContent(ii)) << " "<<hh->GetBinError(ii)*(val/hh->GetBinContent(ii)) << std::endl;
	       hh->SetBinContent(ii, val);
	       hh->SetBinError(ii, err);
	     }
	   }

	   Float_t worig = hh->GetSumOfWeights();
	   Float_t sf = orig/worig;
	   std::cout << "SF = " << sf << std::endl;
	   hh->Scale(sf);
	   hh->Write();

	 }else{
	   obj->Write();
	 }
         delete obj;
     }
  }
  adir->SaveSelf(kTRUE);
  savdir->cd();
}


void CopyFile(const char *fname) {
   //Copy all objects and subdirs of file fname as a subdir of the current directory
   TDirectory *target = gDirectory;
   TFile *f = TFile::Open(fname);
   if (!f || f->IsZombie()) {
      printf("Cannot copy file: %s\n",fname);
      target->cd();
      return;
   }
   target->cd();
   CopyDir(f,0);
   delete f;
   target->cd();
}  

void copyFiles() {
   TFile *f = new TFile("htt_mt.inputs-sm-8TeV.root","recreate");
   CopyFile("htt_mt.inputs-sm-8TeV.backup.root");
   //   f->ls();
   delete f;
}
