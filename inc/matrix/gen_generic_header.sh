#!/usr/bin/bash

# Call the preprocessor on matrix_d.h, matrix_f.h, and matrix_i.h

gcc -E -P matrix_d.h -I../../inc > matrix_d.i
gcc -E -P matrix_f.h -I../../inc > matrix_f.i
gcc -E -P matrix_i.h -I../../inc > matrix_i.i
gcc -E -P matrix_c.h -I../../inc > matrix_c.i

# Now go ahead and compute the line number of the first occurrence 
# of const extern double PI

START_LINE_D=$( grep -n -m1 "extern const double PI" matrix_d.i | cut -f1 -d:)
START_LINE_F=$( grep -n -m1 "extern const double PI" matrix_f.i | cut -f1 -d:)
START_LINE_I=$( grep -n -m1 "extern const double PI" matrix_i.i | cut -f1 -d:)
START_LINE_C=$( grep -n -m1 "extern const double PI" matrix_c.i | cut -f1 -d:)

# Now save the outputs into a single file

HEADER_PREAMBLE=matrix_gen_preamble.h

# Now start writing to the new file

cat $HEADER_PREAMBLE > matrix_gen.h
tail -n +$START_LINE_D matrix_d.i >> matrix_gen.h
tail -n +$START_LINE_F matrix_f.i >> matrix_gen.h
tail -n +$START_LINE_I matrix_i.i >> matrix_gen.h
tail -n +$START_LINE_C matrix_c.i >> matrix_gen.h

rm matrix_i.i
rm matrix_f.i
rm matrix_d.i
rm matrix_c.i

echo "Start_line_d: $START_LINE_D"
echo "Start_line_f: $START_LINE_F"
echo "Start_line_i: $START_LINE_I"
echo "Start_line_c: $START_LINE_I"