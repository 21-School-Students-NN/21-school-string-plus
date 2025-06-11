#!/usr/bin/awk -f

BEGIN {
    # Initialize arrays to store error codes
    linux_const[0] = ""
    linux_desc[""] = ""
    linux_count = 1
    
    xnu_const[0] = ""
    xnu_desc[""] = ""
    xnu_count = 1
}

# Process Linux error codes
FILENAME == "headers/errno-linux.h" {
    if ($1 ~ /^#define/) {
        name = $2
        value = $3

        desc = ""
        for (i = 4; i <= NF; i++) {
            desc = desc " " $i
        }

        # Extract description from comment
        gsub(/^[ \t]*\/\*[ \t]*/, "", desc)
        gsub(/[ \t]*\*\/[ \t]*$/, "", desc)
        
        linux_const[value] = name
        linux_desc[name] = desc
        linux_count++
    }
}

# Process XNU error codes
FILENAME == "headers/errno-xnu.h" {
    if ($1 ~ /^#define/) {
        name = $2
        value = $3

        desc = ""
        for (i = 4; i <= NF; i++) {
            desc = desc " " $i
        }

        # Extract description from comment
        gsub(/^[ \t]*\/\*[ \t]*/, "", desc)
        gsub(/[ \t]*\*\/[ \t]*$/, "", desc)
        
        xnu_const[value] = name
        xnu_desc[name] = desc
        xnu_count++
    }
}

END {  
    # Print header guard and includes
    print "#ifndef S21_SYS_ERRNO_H_"
    print "#define S21_SYS_ERRNO_H_"
    print ""
    
    # Print common error codes
    print "/* Common error codes */"
    for (i = 0; i < linux_count; i++) {
        ln = linux_const[i]
        xn = xnu_const[i]
        if (ln != "" && linux_desc[ln] == xnu_desc[ln] && ln == xn) {
            printf "#define %-20s %-5s /* %s */\n", 
                   ln, i, linux_desc[ln]
        }
    }
    print ""
    
    # Print Linux-specific error codes
    print "#ifdef __linux__ /* Linux-specific error codes */"
    print ""
    for (i = 0; i < linux_count; i++) {
        ln = linux_const[i]
        xn = xnu_const[i]
        if (ln != "" && (linux_desc[ln] != xnu_desc[ln] || ln != xn)) {
            printf "#define %-20s %-5s /* %s */\n", 
                   ln, i, linux_desc[ln]
        }
    }
    print "#endif /* __linux__ */"
    print ""
    
    # Print XNU-specific error codes
    print "#ifdef __APPLE__ /* XNU-specific error codes */"
    print ""
    for (i = 0; i < xnu_count; i++) {
        xn = xnu_const[i]
        ln = linux_const[i]
        if (xn != "" && (linux_desc[xn] != xnu_desc[xn] || xn != ln)) {
            printf "#define %-20s %-5s /* %s */\n", 
                   xn, i, xnu_desc[xn]
        }
    }
    print "#endif /* __APPLE__ */"
    print ""
    
    print "#endif /* _SYS_ERRNO_H_ */"
} 