#!/usr/bin/awk -f

BEGIN {
    print "/* Error message array definitions */"
    print ""
    print "_S(0, \"Success\")"
    print ""
}

/^#define _SYS_ERRNO_H_/ {
    next
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
    
    # Generate _S macro
    printf "#ifdef %s\n", name
    printf "_S(%s, \"%s\")\n", name, desc
    print "#endif"
    print ""
}

# Handle conditional sections
/^#ifdef __linux__/ {
    print "#ifdef __linux__ /* Linux-specific error messages */"
}

/^#ifdef __APPLE__/ {
    print "#ifdef __APPLE__ /* XNU-specific error messages */"
}

/^#endif/ {
    if ($0 ~ /__linux__/) {
        print "#endif /* __linux__ */"
    } else if ($0 ~ /__APPLE__/) {
        print "#endif /* __APPLE__ */"
    }
}