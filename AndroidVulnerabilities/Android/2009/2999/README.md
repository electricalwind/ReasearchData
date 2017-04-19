#CVE-2009-2999
>This vulnerability is linked to the same issue (commit) as the [CVE-2009-2656](../2656/README.MD)

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2009-2999/ "here"

##Description
The com.android.phone process in Android 1.5 CRBxx allows remote attackers to cause a denial of service (application restart and network disconnection) via an SMS message containing a malformed WAP Push message that triggers an ArrayIndexOutOfBoundsException exception, possibly a related issue to CVE-2009-2656.	

##Additionnal Information
* Version Impacted : Android 1.5
* Role of the Component : Messaging

##CVSS Score & Vulnerability Types
* Cvss Score : 4.3
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *None*
* Availbility Impact : *Partial*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : Not Defined