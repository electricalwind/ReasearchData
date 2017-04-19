#CVE-2013-6271
>One Issue found and one corresponding patch

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-6271/ "here"

##Description
Android 4.0 through 4.3 allows attackers to bypass intended access restrictions and remove device locks via a crafted application that invokes the updateUnlockMethodAndFinish method in the com.android.settings.ChooseLockGeneric class with the PASSWORD_QUALITY_UNSPECIFIED option.	

##Additionnal Information
* Version Impacted : Android 4.0 to 4.3
* Role of the Component : Access Control

##CVSS Score & Vulnerability Types
* Cvss Score : 8.8
* CVSS Access : *Network*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *None*
* Access Complexity : *Medium*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

##Corresponding Issue
###Complexity
* **Cycc total**: 8
* **Total Commit**: 1
* **Total modified file**: 3
* **Cloc**: 12


##Patch
####Description
Make sure that external callers cannot pass in the confirm bypass extra

Security fix for vulnerability where an app could launch into the screen lock
change dialog without first confirming the existing password/pattern.

Also, make sure that the fragments are launched with the correct corresponding
activity.


####Origin
* Language : Java
* Origin of the issue :  Design -> Flow
* Location : [platform/packages/apps/Settings] (https://android.googlesource.com/platform/packages/apps/Settings/)

####Patch
* **Kind of Patch** : Add Condition / Exception raising

|  Complexity | Before | After |
|---------------------------------|--------|-------|
| Essential Cyclomatic Complexity |    1    |     1   |
| Extended Cyclomatic Complexity  |      6    |    6    |
| Cyclomatic complexity           |      6    |   6      |
 

You can find here [the corresponding commit] (https://android.googlesource.com/platform/packages/apps/Settings/+/66026773bbf1d7631743a5b892a4f768c694f868%5E%21/#F1) , the patch [in this folder] (patch/),
[Additional ressource](http://blog.curesec.com/article/blog/26.html) and the
[exploit](exploit/)
 
