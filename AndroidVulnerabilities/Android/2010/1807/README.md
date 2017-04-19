#CVE-2010-1807
>1 Corresponding Issue (one commit) and 2 patched files in it .

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2010-1807/ "here"

##Description
WebKit in Apple Safari 4.x before 4.1.2 and 5.x before 5.0.2; Android before 2.2; and webkitgtk before 1.2.6; does not properly validate floating-point data, which allows remote attackers to execute arbitrary code or cause a denial of service (application crash) via a crafted HTML document, related to non-standard NaN representation.	
##Additionnal Information
* Version Impacted : Android 1.0 to 2.1
* Role of the Component : Browsing

##CVSS Score & Vulnerability Types
* Cvss Score : 9.3
* CVSS Access : *Network*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [20] (http://cwe.mitre.org/data/definitions/20.html) 

##Corresponding Issue

###Complexity
* **Cycc total**: 3
* **Total Commit**: 1
* **Total modified file**: 2
* **Cloc**: 3


###Description
JavaScriptCore: ​https://bugs.webkit.org/show_bug.cgi?id=43461
Invalid NaN parsing

Reviewed by Oliver Hunt and Beth Dakin.
wtf/dtoa.cpp: Turn off the dtoa feature that allows you to specify a
non-standard NaN representation, since our NaN encoding assumes that all
true NaNs have the standard bit pattern.
API/JSValueRef.cpp:
(JSValueMakeNumber): Don't allow an API client to accidentally specify
a non-standard NaN either.
LayoutTests: ​https://bugs.webkit.org/show_bug.cgi?id=43461
Crash parsing certain values for NaN
Reviewed by Oliver Hunt and Beth Dakin.
fast/js/parse-nan.html: Added.
fast/js/script-tests/parse-nan.js: Added.

Location : [WebKit Framework] (http://trac.webkit.org/)
You can find here [the corresponding commit] (http://trac.webkit.org/changeset/64706)  
###Patch 1 
####Origin
* Language : CPP
* Origin of the issue : Code -> Data -> Input Not Verified

####Patch
* **Kind of Patch** : Add Condition
* **Cycc** : 2
* **Cloc** : 2

Corresponding files [in this folder] (patch1/).

###Patch 2
####Origin
* Language : CPP
* Origin of the issue : Code -> Semantic -> Missing or Incorrect implementation of a feature

#####Patch
  * **Kind of Patch** : Add Define
  * **Cycc** : 1
  * **Cloc** : 1
  
Corresponding files [in this folder] (patch2/).

