#!/usr/bin/awk -f

BEGIN {
    print "#ifndef _S21_ERROR_MESSAGES_H_"
    print "#define _S21_ERROR_MESSAGES_H_"
    print ""
    print "/* Error message array definitions */"
    print "#define N_(msg) msg"
    print "#define ERR_MAP(n) n"
    print ""
    print "_S(ERR_MAP(0), N_(\"Success\"))"
}

# Process error codes
/^#define/ {
    name = $2
    value = $3
    # Extract description from comment
    desc = ""
    for (i = 4; i <= NF; i++) {
        desc = desc " " $i
    }
    gsub(/^[ \t]*\/\*[ \t]*/, "", desc)
    gsub(/[ \t]*\*\/[ \t]*$/, "", desc)
    
    # Skip if it's a conditional definition
    if (name ~ /^#/) next
    
    # Generate _S macro
    printf "#ifdef %s\n", name
    printf "_S(ERR_MAP(%s), N_(\"%s\"))\n", name, desc
    print "#endif"
    print ""
}

# Handle conditional sections
/^#ifdef __linux__/ {
    print "#ifdef __linux__"
    print "/* Linux-specific error messages */"
}

/^#ifdef __APPLE__/ {
    print "#ifdef __APPLE__"
    print "/* XNU-specific error messages */"
}

/^#endif/ {
    if ($0 ~ /__linux__/) {
        print "#endif /* __linux__ */"
    } else if ($0 ~ /__APPLE__/) {
        print "#endif /* __APPLE__ */"
    }
}

END {
    print ""
    print "#undef ERR_MAP"
    print "#undef N_"
    print "#endif /* _S21_ERROR_MESSAGES_H_ */"
} 