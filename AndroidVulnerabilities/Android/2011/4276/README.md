#CVE-2011-4276
>6 corresponding commits were found.
>This vulnerability require too much computation for a manual processing

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2011-4276/ "here"

##Description
The Bluetooth service (com/android/phone/BluetoothHeadsetService.java) in Android 2.3 before 2.3.6 allows remote attackers within Bluetooth range to obtain contact data via an AT phonebook transfer.

##Additionnal Information
* Version Impacted : Android 2.3 to 2.3.5
* Component : Network


##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *None*
* Availbility Impact : *None*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [200] (http://cwe.mitre.org/data/definitions/200.html) 

##Corresponding Bug
###Complexity
* **Cycc total**: >25
* **Total Commit**: 6
* **Total modified file**: 11+1+1+1+4+1 = 19
* **Cloc**: 395+ 17 + 3 + 2 +196 +11 = 624


Due to the high number of patch and modification, the manual computation of cycc is not possible.

###Patch 1
####Description
This sends the intents to the Settings app to show
the dialogs for the incoming connection requests.

###Patch 2
####Description
Add binder call for the above.
BluetoothHeadsetService.java

###Patch 3
####Description
This is for the user dialog for incoming BT requests.

###Patch 4
####Description
No Description

###Patch 5
####Description
Show user dialog for incoming BT connection
requests from unknown devices.

###Patch 6
####Description
No Description
