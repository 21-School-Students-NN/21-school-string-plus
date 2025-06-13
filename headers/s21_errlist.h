/* Error message array definitions */

_S(0, "Success")

#ifdef EPERM
_S(EPERM, "Operation not permitted")
#endif

#ifdef ENOENT
_S(ENOENT, "No such file or directory")
#endif

#ifdef ESRCH
_S(ESRCH, "No such process")
#endif

#ifdef EINTR
_S(EINTR, "Interrupted system call")
#endif

#ifdef EIO
_S(EIO, "Input/output error")
#endif

#ifdef E2BIG
_S(E2BIG, "Argument list too long")
#endif

#ifdef ENOEXEC
_S(ENOEXEC, "Exec format error")
#endif

#ifdef EBADF
_S(EBADF, "Bad file descriptor")
#endif

#ifdef ECHILD
_S(ECHILD, "No child processes")
#endif

#ifdef ENOMEM
_S(ENOMEM, "Cannot allocate memory")
#endif

#ifdef EACCES
_S(EACCES, "Permission denied")
#endif

#ifdef EFAULT
_S(EFAULT, "Bad address")
#endif

#ifdef ENOTBLK
_S(ENOTBLK, "Block device required")
#endif

#ifdef EEXIST
_S(EEXIST, "File exists")
#endif

#ifdef ENOTDIR
_S(ENOTDIR, "Not a directory")
#endif

#ifdef EISDIR
_S(EISDIR, "Is a directory")
#endif

#ifdef EINVAL
_S(EINVAL, "Invalid argument")
#endif

#ifdef ENFILE
_S(ENFILE, "Too many open files in system")
#endif

#ifdef EMFILE
_S(EMFILE, "Too many open files")
#endif

#ifdef ENOTTY
_S(ENOTTY, "Inappropriate ioctl for device")
#endif

#ifdef ETXTBSY
_S(ETXTBSY, "Text file busy")
#endif

#ifdef EFBIG
_S(EFBIG, "File too large")
#endif

#ifdef ENOSPC
_S(ENOSPC, "No space left on device")
#endif

#ifdef ESPIPE
_S(ESPIPE, "Illegal seek")
#endif

#ifdef EROFS
_S(EROFS, "Read-only file system")
#endif

#ifdef EMLINK
_S(EMLINK, "Too many links")
#endif

#ifdef EPIPE
_S(EPIPE, "Broken pipe")
#endif

#ifdef EDOM
_S(EDOM, "Numerical argument out of domain")
#endif

#ifdef __linux__ /* Linux-specific error messages */
#ifdef ENXIO
_S(ENXIO, "No such device or address")
#endif

#ifdef EAGAIN
_S(EAGAIN, "Resource temporarily unavailable")
#endif

#ifdef EBUSY
_S(EBUSY, "Device or resource busy")
#endif

#ifdef EXDEV
_S(EXDEV, "Invalid cross-device link")
#endif

#ifdef ENODEV
_S(ENODEV, "No such device")
#endif

#ifdef ERANGE
_S(ERANGE, "Numerical result out of range")
#endif

#ifdef EDEADLK
_S(EDEADLK, "Resource deadlock avoided")
#endif

#ifdef ENAMETOOLONG
_S(ENAMETOOLONG, "File name too long")
#endif

#ifdef ENOLCK
_S(ENOLCK, "No locks available")
#endif

#ifdef ENOSYS
_S(ENOSYS, "Function not implemented")
#endif

#ifdef ENOTEMPTY
_S(ENOTEMPTY, "Directory not empty")
#endif

#ifdef ELOOP
_S(ELOOP, "Too many levels of symbolic links")
#endif

#ifdef ENOMSG
_S(ENOMSG, "No message of desired type")
#endif

#ifdef EIDRM
_S(EIDRM, "Identifier removed")
#endif

#ifdef ECHRNG
_S(ECHRNG, "Channel number out of range")
#endif

#ifdef EL2NSYNC
_S(EL2NSYNC, "Level 2 not synchronized")
#endif

#ifdef EL3HLT
_S(EL3HLT, "Level 3 halted")
#endif

#ifdef EL3RST
_S(EL3RST, "Level 3 reset")
#endif

#ifdef ELNRNG
_S(ELNRNG, "Link number out of range")
#endif

#ifdef EUNATCH
_S(EUNATCH, "Protocol driver not attached")
#endif

#ifdef ENOCSI
_S(ENOCSI, "No CSI structure available")
#endif

#ifdef EL2HLT
_S(EL2HLT, "Level 2 halted")
#endif

#ifdef EBADE
_S(EBADE, "Invalid exchange")
#endif

#ifdef EBADR
_S(EBADR, "Invalid request descriptor")
#endif

#ifdef EXFULL
_S(EXFULL, "Exchange full")
#endif

#ifdef ENOANO
_S(ENOANO, "No anode")
#endif

#ifdef EBADRQC
_S(EBADRQC, "Invalid request code")
#endif

#ifdef EBADSLT
_S(EBADSLT, "Invalid slot")
#endif

#ifdef EBFONT
_S(EBFONT, "Bad font file format")
#endif

#ifdef ENOSTR
_S(ENOSTR, "Device not a stream")
#endif

#ifdef ENODATA
_S(ENODATA, "No data available")
#endif

#ifdef ETIME
_S(ETIME, "Timer expired")
#endif

#ifdef ENOSR
_S(ENOSR, "Out of streams resources")
#endif

#ifdef ENONET
_S(ENONET, "Machine is not on the network")
#endif

#ifdef ENOPKG
_S(ENOPKG, "Package not installed")
#endif

#ifdef EREMOTE
_S(EREMOTE, "Object is remote")
#endif

#ifdef ENOLINK
_S(ENOLINK, "Link has been severed")
#endif

#ifdef EADV
_S(EADV, "Advertise error")
#endif

#ifdef ESRMNT
_S(ESRMNT, "Srmount error")
#endif

#ifdef ECOMM
_S(ECOMM, "Communication error on send")
#endif

#ifdef EPROTO
_S(EPROTO, "Protocol error")
#endif

#ifdef EMULTIHOP
_S(EMULTIHOP, "Multihop attempted")
#endif

#ifdef EDOTDOT
_S(EDOTDOT, "RFS specific error")
#endif

#ifdef EBADMSG
_S(EBADMSG, "Bad message")
#endif

#ifdef EOVERFLOW
_S(EOVERFLOW, "Value too large for defined data type")
#endif

#ifdef ENOTUNIQ
_S(ENOTUNIQ, "Name not unique on network")
#endif

#ifdef EBADFD
_S(EBADFD, "File descriptor in bad state")
#endif

#ifdef EREMCHG
_S(EREMCHG, "Remote address changed")
#endif

#ifdef ELIBACC
_S(ELIBACC, "Can not access a needed shared library")
#endif

#ifdef ELIBBAD
_S(ELIBBAD, "Accessing a corrupted shared library")
#endif

#ifdef ELIBSCN
_S(ELIBSCN, ".lib section in a.out corrupted")
#endif

#ifdef ELIBMAX
_S(ELIBMAX, "Attempting to link in too many shared libraries")
#endif

#ifdef ELIBEXEC
_S(ELIBEXEC, "Cannot exec a shared library directly")
#endif

#ifdef EILSEQ
_S(EILSEQ, "Invalid or incomplete multibyte or wide character")
#endif

#ifdef ERESTART
_S(ERESTART, "Interrupted system call should be restarted")
#endif

#ifdef ESTRPIPE
_S(ESTRPIPE, "Streams pipe error")
#endif

#ifdef EUSERS
_S(EUSERS, "Too many users")
#endif

#ifdef ENOTSOCK
_S(ENOTSOCK, "Socket operation on non-socket")
#endif

#ifdef EDESTADDRREQ
_S(EDESTADDRREQ, "Destination address required")
#endif

#ifdef EMSGSIZE
_S(EMSGSIZE, "Message too long")
#endif

#ifdef EPROTOTYPE
_S(EPROTOTYPE, "Protocol wrong type for socket")
#endif

#ifdef ENOPROTOOPT
_S(ENOPROTOOPT, "Protocol not available")
#endif

#ifdef EPROTONOSUPPORT
_S(EPROTONOSUPPORT, "Protocol not supported")
#endif

#ifdef ESOCKTNOSUPPORT
_S(ESOCKTNOSUPPORT, "Socket type not supported")
#endif

#ifdef EOPNOTSUPP
_S(EOPNOTSUPP, "Operation not supported")
#endif

#ifdef EPFNOSUPPORT
_S(EPFNOSUPPORT, "Protocol family not supported")
#endif

#ifdef EAFNOSUPPORT
_S(EAFNOSUPPORT, "Address family not supported by protocol")
#endif

#ifdef EADDRINUSE
_S(EADDRINUSE, "Address already in use")
#endif

#ifdef EADDRNOTAVAIL
_S(EADDRNOTAVAIL, "Cannot assign requested address")
#endif

#ifdef ENETDOWN
_S(ENETDOWN, "Network is down")
#endif

#ifdef ENETUNREACH
_S(ENETUNREACH, "Network is unreachable")
#endif

#ifdef ENETRESET
_S(ENETRESET, "Network dropped connection on reset")
#endif

#ifdef ECONNABORTED
_S(ECONNABORTED, "Software caused connection abort")
#endif

#ifdef ECONNRESET
_S(ECONNRESET, "Connection reset by peer")
#endif

#ifdef ENOBUFS
_S(ENOBUFS, "No buffer space available")
#endif

#ifdef EISCONN
_S(EISCONN, "Transport endpoint is already connected")
#endif

#ifdef ENOTCONN
_S(ENOTCONN, "Transport endpoint is not connected")
#endif

#ifdef ESHUTDOWN
_S(ESHUTDOWN, "Cannot send after transport endpoint shutdown")
#endif

#ifdef ETOOMANYREFS
_S(ETOOMANYREFS, "Too many references: cannot splice")
#endif

#ifdef ETIMEDOUT
_S(ETIMEDOUT, "Connection timed out")
#endif

#ifdef ECONNREFUSED
_S(ECONNREFUSED, "Connection refused")
#endif

#ifdef EHOSTDOWN
_S(EHOSTDOWN, "Host is down")
#endif

#ifdef EHOSTUNREACH
_S(EHOSTUNREACH, "No route to host")
#endif

#ifdef EALREADY
_S(EALREADY, "Operation already in progress")
#endif

#ifdef EINPROGRESS
_S(EINPROGRESS, "Operation now in progress")
#endif

#ifdef ESTALE
_S(ESTALE, "Stale file handle")
#endif

#ifdef EUCLEAN
_S(EUCLEAN, "Structure needs cleaning")
#endif

#ifdef ENOTNAM
_S(ENOTNAM, "Not a XENIX named type file")
#endif

#ifdef ENAVAIL
_S(ENAVAIL, "No XENIX semaphores available")
#endif

#ifdef EISNAM
_S(EISNAM, "Is a named type file")
#endif

#ifdef EREMOTEIO
_S(EREMOTEIO, "Remote I/O error")
#endif

#ifdef EDQUOT
_S(EDQUOT, "Disk quota exceeded")
#endif

#ifdef ENOMEDIUM
_S(ENOMEDIUM, "No medium found")
#endif

#ifdef EMEDIUMTYPE
_S(EMEDIUMTYPE, "Wrong medium type")
#endif

#ifdef ECANCELED
_S(ECANCELED, "Operation canceled")
#endif

#ifdef ENOKEY
_S(ENOKEY, "Required key not available")
#endif

#ifdef EKEYEXPIRED
_S(EKEYEXPIRED, "Key has expired")
#endif

#ifdef EKEYREVOKED
_S(EKEYREVOKED, "Key has been revoked")
#endif

#ifdef EKEYREJECTED
_S(EKEYREJECTED, "Key was rejected by service")
#endif

#ifdef EOWNERDEAD
_S(EOWNERDEAD, "Owner died")
#endif

#ifdef ENOTRECOVERABLE
_S(ENOTRECOVERABLE, "State not recoverable")
#endif

#ifdef ERFKILL
_S(ERFKILL, "Operation not possible due to RF-kill")
#endif

#ifdef EHWPOISON
_S(EHWPOISON, "Memory page has hardware error")
#endif

#endif /* __linux__ */
#ifdef __APPLE__ /* XNU-specific error messages */
#ifdef ENXIO
_S(ENXIO, "Device not configured")
#endif

#ifdef EDEADLK
_S(EDEADLK, "Resource deadlock avoided")
#endif

#ifdef EBUSY
_S(EBUSY, "Device / Resource busy")
#endif

#ifdef EXDEV
_S(EXDEV, "Cross-device link")
#endif

#ifdef ENODEV
_S(ENODEV, "Operation not supported by device")
#endif

#ifdef ERANGE
_S(ERANGE, "Result too large")
#endif

#ifdef EAGAIN
_S(EAGAIN, "Resource temporarily unavailable")
#endif

#ifdef EINPROGRESS
_S(EINPROGRESS, "Operation now in progress")
#endif

#ifdef EALREADY
_S(EALREADY, "Operation already in progress")
#endif

#ifdef ENOTSOCK
_S(ENOTSOCK, "Socket operation on non-socket")
#endif

#ifdef EDESTADDRREQ
_S(EDESTADDRREQ, "Destination address required")
#endif

#ifdef EMSGSIZE
_S(EMSGSIZE, "Message too long")
#endif

#ifdef EPROTOTYPE
_S(EPROTOTYPE, "Protocol wrong type for socket")
#endif

#ifdef ENOPROTOOPT
_S(ENOPROTOOPT, "Protocol not available")
#endif

#ifdef EPROTONOSUPPORT
_S(EPROTONOSUPPORT, "Protocol not supported")
#endif

#ifdef ESOCKTNOSUPPORT
_S(ESOCKTNOSUPPORT, "Socket type not supported")
#endif

#ifdef ENOTSUP
_S(ENOTSUP, "Operation not supported")
#endif

#ifdef EPFNOSUPPORT
_S(EPFNOSUPPORT, "Protocol family not supported")
#endif

#ifdef EAFNOSUPPORT
_S(EAFNOSUPPORT, "Address family not supported by protocol family")
#endif

#ifdef EADDRINUSE
_S(EADDRINUSE, "Address already in use")
#endif

#ifdef EADDRNOTAVAIL
_S(EADDRNOTAVAIL, "Can't assign requested address")
#endif

#ifdef ENETDOWN
_S(ENETDOWN, "Network is down")
#endif

#ifdef ENETUNREACH
_S(ENETUNREACH, "Network is unreachable")
#endif

#ifdef ENETRESET
_S(ENETRESET, "Network dropped connection on reset")
#endif

#ifdef ECONNABORTED
_S(ECONNABORTED, "Software caused connection abort")
#endif

#ifdef ECONNRESET
_S(ECONNRESET, "Connection reset by peer")
#endif

#ifdef ENOBUFS
_S(ENOBUFS, "No buffer space available")
#endif

#ifdef EISCONN
_S(EISCONN, "Socket is already connected")
#endif

#ifdef ENOTCONN
_S(ENOTCONN, "Socket is not connected")
#endif

#ifdef ESHUTDOWN
_S(ESHUTDOWN, "Can't send after socket shutdown")
#endif

#ifdef ETOOMANYREFS
_S(ETOOMANYREFS, "Too many references: can't splice")
#endif

#ifdef ETIMEDOUT
_S(ETIMEDOUT, "Operation timed out")
#endif

#ifdef ECONNREFUSED
_S(ECONNREFUSED, "Connection refused")
#endif

#ifdef ELOOP
_S(ELOOP, "Too many levels of symbolic links")
#endif

#ifdef ENAMETOOLONG
_S(ENAMETOOLONG, "File name too long")
#endif

#ifdef EHOSTDOWN
_S(EHOSTDOWN, "Host is down")
#endif

#ifdef EHOSTUNREACH
_S(EHOSTUNREACH, "No route to host")
#endif

#ifdef ENOTEMPTY
_S(ENOTEMPTY, "Directory not empty")
#endif

#ifdef EPROCLIM
_S(EPROCLIM, "Too many processes")
#endif

#ifdef EUSERS
_S(EUSERS, "Too many users")
#endif

#ifdef EDQUOT
_S(EDQUOT, "Disc quota exceeded")
#endif

#ifdef ESTALE
_S(ESTALE, "Stale NFS file handle")
#endif

#ifdef EREMOTE
_S(EREMOTE, "Too many levels of remote in path")
#endif

#ifdef EBADRPC
_S(EBADRPC, "RPC struct is bad")
#endif

#ifdef ERPCMISMATCH
_S(ERPCMISMATCH, "RPC version wrong")
#endif

#ifdef EPROGUNAVAIL
_S(EPROGUNAVAIL, "RPC prog. not avail")
#endif

#ifdef EPROGMISMATCH
_S(EPROGMISMATCH, "Program version wrong")
#endif

#ifdef EPROCUNAVAIL
_S(EPROCUNAVAIL, "Bad procedure for program")
#endif

#ifdef ENOLCK
_S(ENOLCK, "No locks available")
#endif

#ifdef ENOSYS
_S(ENOSYS, "Function not implemented")
#endif

#ifdef EFTYPE
_S(EFTYPE, "Inappropriate file type or format")
#endif

#ifdef EAUTH
_S(EAUTH, "Authentication error")
#endif

#ifdef ENEEDAUTH
_S(ENEEDAUTH, "Need authenticator")
#endif

#ifdef EPWROFF
_S(EPWROFF, "Device power is off")
#endif

#ifdef EDEVERR
_S(EDEVERR, "Device error, e.g. paper out")
#endif

#ifdef EOVERFLOW
_S(EOVERFLOW, "Value too large to be stored in data type")
#endif

#ifdef EBADEXEC
_S(EBADEXEC, "Bad executable")
#endif

#ifdef EBADARCH
_S(EBADARCH, "Bad CPU type in executable")
#endif

#ifdef ESHLIBVERS
_S(ESHLIBVERS, "Shared library version mismatch")
#endif

#ifdef EBADMACHO
_S(EBADMACHO, "Malformed Macho file")
#endif

#ifdef ECANCELED
_S(ECANCELED, "Operation canceled")
#endif

#ifdef EIDRM
_S(EIDRM, "Identifier removed")
#endif

#ifdef ENOMSG
_S(ENOMSG, "No message of desired type")
#endif

#ifdef EILSEQ
_S(EILSEQ, "Illegal byte sequence")
#endif

#ifdef ENOATTR
_S(ENOATTR, "Attribute not found")
#endif

#ifdef EBADMSG
_S(EBADMSG, "Bad message")
#endif

#ifdef EMULTIHOP
_S(EMULTIHOP, "Reserved")
#endif

#ifdef ENODATA
_S(ENODATA, "No message available on STREAM")
#endif

#ifdef ENOLINK
_S(ENOLINK, "Reserved")
#endif

#ifdef ENOSR
_S(ENOSR, "No STREAM resources")
#endif

#ifdef ENOSTR
_S(ENOSTR, "Not a STREAM")
#endif

#ifdef EPROTO
_S(EPROTO, "Protocol error")
#endif

#ifdef ETIME
_S(ETIME, "STREAM ioctl timeout")
#endif

#ifdef EOPNOTSUPP
_S(EOPNOTSUPP, "Operation not supported on socket")
#endif

#ifdef ENOPOLICY
_S(ENOPOLICY, "No such policy registered")
#endif

#ifdef ENOTRECOVERABLE
_S(ENOTRECOVERABLE, "State not recoverable")
#endif

#ifdef EOWNERDEAD
_S(EOWNERDEAD, "Previous owner died")
#endif

#ifdef ELAST
_S(ELAST, "Must be equal largest errno")
#endif

#ifdef EQFULL
_S(EQFULL, "Interface output queue is full")
#endif

#ifdef EWOULDBLOCK
_S(EWOULDBLOCK, "Operation would block")
#endif

#ifdef EOPNOTSUPP
_S(EOPNOTSUPP, "Operation not supported on socket")
#endif

#endif /* __APPLE__ */
