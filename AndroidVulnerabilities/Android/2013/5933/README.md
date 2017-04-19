#CVE-2013-5933
>possibly link to [CVE-2013-4777](../4777/README.md)

More details [here].
[here]: http://www.cvedetails.com/cve/CVE-2013-5933/ "here"

##Description
Stack-based buffer overflow in the sub_E110 function in init in a certain configuration of Android 2.3.7 on the Motorola Defy XT phone for Republic Wireless allows local users to gain privileges or cause a denial of service (memory corruption) by writing a long string to the /dev/socket/init_runit socket that is inconsistent with a certain length value that was previously written to this socket.

##Additionnal Information
* Version Impacted : Android 
* Role of the Component : Networking
* Vendor Specific : Motorola

##CVSS Score & Vulnerability Types
* Cvss Score : 6.9
* CVSS Access : *Local*
* Confidentiality Impact : *Complete*
* Integrity Impact : *Complete*
* Availbility Impact : *Complete*
* Access Complexity : *Medium*
* Authentication : *Not required*
* Gained Access : *None*
* CWE : [119] (http://cwe.mitre.org/data/definitions/199.html) 

##Corresponding Issue
####Description
 this "feature" actually has a trivial stack-based buffer overflow in it. In sub_E110() of the Defy XT's init binary (where this functionality is implemented), something akin to the following happens:

    char buf[1024];
    int fd;
    unsigned short len;
    ...

    fd = accept(runit_socket, &addr, &addrlen);
    ...

    recv(fd, &len, 2, 0);
    recv(fd, buf, len, 0);


The length of the second recv() is provided entirely by the user connecting to the socket. The maximum value for an unsigned short, 0xffff, is more than sufficient to cause a stack-based buffer overflow. There's no stack cookie in this function, and the compiler has graciously used a PUSH.W {R4-R8,LR} / POP.W {R4-R8,PC} prologue and epilogue for this function to make exploitation nice and easy. So just in case passing arbitrary data to a popen() call is too easy, you've got a memory corruption vulnerability to play with as well.

####Origin
* Language : Java
* Origin of the issue : Code -> Buffer Overflow

####Patch
No patch planned

You can find here [the corresponding explanation] (https://plus.google.com/+JustinCaseAndroid/posts/5ofgPNrSu3J)  and the vulnerable file [in this folder] (vulnerablecode/).