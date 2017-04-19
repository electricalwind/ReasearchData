#CVE-2008-7298
>No Corresponding issue was found for this vulnerability.

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2008-7298/ "here"

##Description
The Android browser in Android cannot properly restrict modifications to cookies established in HTTPS sessions, which allows man-in-the-middle attackers to overwrite or delete arbitrary cookies via a Set-Cookie header in an HTTP response, related to lack of the HTTP Strict Transport Security (HSTS) includeSubDomains feature, aka a "cookie forcing" issue.	

##Additionnal Information
* Version Impacted : Android 1.5
* Role of the Component : Cryptography

##CVSS Score & Vulnerability Types
* Cvss Score : 5.8
* CVSS Access : *Network*
* Confidentiality Impact : *None*
* Integrity Impact : *Partial*
* Availbility Impact : *Partial*
* Access Complexity : *Medium*
* Authentication : *Not Required*
* Gained Access : *None*
* CWE : [264] (http://cwe.mitre.org/data/definitions/264.html) 

