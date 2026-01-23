import pytest

def test_input_output_filter(input_file, output_file):
    """
    Input format:
    {Number}

    Output format: 
    {Input Number} {PASS/FAIL} [if FAIL {Reason for FAIL}]
    """
    lower=-800
    upper=3000

    fail=False

    with open(input_file, "r") as infile:
       with open(output_file, "w") as outfile:
            lines = infile.readlines()
            for line in lines:
                val=int(line)
                if val<lower:
                    newline=f"{val} FAIL LOW"
                    fail=True
                elif val>upper:
                    newline=f"{val} FAIL HIGH"
                    fail=True
                else:
                    newline=f"{val} PASS"
                outfile.write(newline + "\n")
            
    assert not fail, "failed"