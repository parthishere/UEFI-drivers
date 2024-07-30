[Defines]
    INF_VERSION  = 0x00010006                 
    BASE_NAME    = SimpleShellApp     
    FILE_GUID    = 35c3ac36-4d6f-45c6-a3f9-d89ec1a02995  
    MODULE_TYPE  = UEFI_APPLICATION      
    VERSION_STRING = 1.0         
    ENTRY_POINT  = ShellCEntryLib      
[Sources]
    SimpleShellApp.c
[Packages]
    MdePkg/MdePkg.dec
[LibraryClasses]
    ShellCEntryLib
    