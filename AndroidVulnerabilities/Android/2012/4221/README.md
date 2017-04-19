#CVE-2012-4221
> Same Patch as [CVE-2012-4220](../4220/README.md)

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2012-4221/ "here"

##Description
Integer overflow in diagchar_core.c in the Qualcomm Innovation Center (QuIC) Diagnostics (aka DIAG) kernel-mode driver for Android 2.3 through 4.2 allows attackers to execute arbitrary code or cause a denial of service via an application that uses crafted arguments in a local diagchar_ioctl call.	

##Additionnal Information
* Version Impacted : Android 2.3 to 4.2
* Role of the Component : Driver
* Vendor Specific : Qualcomm

##CVSS Score & Vulnerability Types
* Cvss Score : 6.8
* CVSS Access : *Network*
* Confidentiality Impact : *Partial*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [189](http://cwe.mitre.org/data/definitions/189.html) 

##Patch 
See [CVE-2012-4220](../4220/README.md)



