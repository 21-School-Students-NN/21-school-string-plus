#!/usr/bin/awk -f

BEGIN {
    # Initialize arrays to store error codes
    linux_codes[""] = 0
    linux_desc[""] = ""
    
    xnu_codes[""] = 0
    xnu_desc[""] = ""
    # Array to store all error codes for sorting
    all_codes[0] = ""
    code_count = 0
}

# Process Linux error codes
FILENAME == "headers/errno-linux.h" {
    if ($1 ~ /^#define/) {
        name = $2
        value = $3
        # Extract description from comment
        desc = ""
        for (i = 4; i <= NF; i++) {
            desc = desc " " $i
        }
        gsub(/^[ \t]*\/\*[ \t]*/, "", desc)
        gsub(/[ \t]*\*\/[ \t]*$/, "", desc)
        
        linux_codes[name] = value
        linux_desc[name] = desc
        
        # Store for sorting
        all_codes[code_count++] = name
    }
}

# Process XNU error codes
FILENAME == "headers/errno-xnu.h" {
    if ($1 ~ /^#define/) {
        name = $2
        value = $3
        # Extract description from comment
        desc = ""
        for (i = 4; i <= NF; i++) {
            desc = desc " " $i
        }
        gsub(/^[ \t]*\/\*[ \t]*/, "", desc)
        gsub(/[ \t]*\*\/[ \t]*$/, "", desc)
        
        xnu_codes[name] = value
        xnu_desc[name] = desc
        
        # Store for sorting if not already stored
        if (!(name in linux_codes)) {
            all_codes[code_count++] = name
        }
    }
}

# Sort function
function sort_codes(arr, n) {
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            val1 = linux_codes[arr[j]] ? linux_codes[arr[j]] : xnu_codes[arr[j]]
            val2 = linux_codes[arr[j+1]] ? linux_codes[arr[j+1]] : xnu_codes[arr[j+1]]
            if (val1 > val2 || (val1 == val2 && arr[j] > arr[j+1])) {
                temp = arr[j]
                arr[j] = arr[j+1]
                arr[j+1] = temp
            }
        }
    }
}

END {
    # Sort the error codes
    sort_codes(all_codes, code_count)
    
    # Print header guard and includes
    print "#ifndef _SYS_ERRNO_H_"
    print "#define _SYS_ERRNO_H_"
    print ""
    
    # Print common error codes
    print "/* Common error codes */"
    for (i = 0; i < code_count; i++) {
        name = all_codes[i]
        if (name != "" && linux_codes[name] != "" && xnu_codes[name] != "" && 
            linux_codes[name] == xnu_codes[name] && 
            linux_desc[name] == xnu_desc[name]) {
            printf "#define %-20s %-5s /* %s */\n", 
                   name, linux_codes[name], linux_desc[name]
        }
    }
    print ""
    
    # Print Linux-specific error codes
    print "#ifdef __linux__"
    print "/* Linux-specific error codes */"
    for (i = 0; i < code_count; i++) {
        name = all_codes[i]
        if (name != "" && linux_codes[name] != "" && 
            (xnu_codes[name] == "" || 
             linux_codes[name] != xnu_codes[name] || 
             linux_desc[name] != xnu_desc[name])) {
            printf "#define %-20s %-5s /* %s */\n", 
                   name, linux_codes[name], linux_desc[name]
        }
    }
    print "#endif /* __linux__ */"
    print ""
    
    # Print XNU-specific error codes
    print "#ifdef __APPLE__"
    print "/* XNU-specific error codes */"
    for (i = 0; i < code_count; i++) {
        name = all_codes[i]
        if (name != "" && xnu_codes[name] != "" && 
            (linux_codes[name] == "" || 
             linux_codes[name] != xnu_codes[name] || 
             linux_desc[name] != xnu_desc[name])) {
            printf "#define %-20s %-5s /* %s */\n", 
                   name, xnu_codes[name], xnu_desc[name]
        }
    }
    print "#endif /* __APPLE__ */"
    print ""
    
    print "#endif /* _SYS_ERRNO_H_ */"
} 