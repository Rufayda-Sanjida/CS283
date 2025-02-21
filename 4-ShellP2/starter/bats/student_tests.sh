#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Change to home directory and print working directory" {
    run "./dsh" <<EOF
cd ~
pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "/home/" ]] || [[ "$output" =~ "/Users/" ]]
}


@test "Exit command should terminate shell" {
    run "./dsh" <<EOF
exit
EOF

    [ "$status" -eq 0 ]
}

@test "Piping ls to wc -l" {
    run "./dsh" <<EOF
ls | wc -l
EOF

    [ "$status" -eq 0 ]
}

@test "Ensure empty command is handled correctly" {
    run "./dsh" <<EOF

EOF

    [ "$status" -eq 0 ]
    [[ "$output" == *"$SH_PROMPT"* ]]
}


@test "Change to a specific directory and verify" {
    run "./dsh" <<EOF
mkdir -p testdir
cd testdir
pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" == *"/testdir"* ]]
}


@test "Run multiple commands in sequentially" {
    run "./dsh" <<EOF
echo "cat one"
echo "cat two"
echo "cat three"
EOF

    cleaned_output=$(echo "$output" | grep -v "dsh2>" | tr -d '[:space:]')
    expected="catonecattwocatthreecmdloopreturned0"

    echo "Raw Output: $output"
    echo "Processed Output: $cleaned_output"
    [ "$cleaned_output" = "$expected" ]
    [ "$status" -eq 0 ]
}

