#!/usr/bin/env bash

dpr_calc="$1"
dpr_sample="$(dirname $0)/dpr-sample.txt"
param="-d 12 -ac 8"
result="$(dirname $0)/dpr-test.txt"

if [ -z ${dpr_calc} ]; then
  echo "Error: Supply the path to the dpr-calc binary."
  exit 1
fi

echo "Testing dpr-calc, creating result file: ${result}"
touch ${result}

# Case 1: -d 12 -ac 8
${dpr_calc} ${param} > ${result}
echo "" >> ${result}
${dpr_calc} ${param} -adv >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -dis >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -elf >> ${result}
echo "" >> ${result}

# Case 2: -d 12 -ac 8 -b 30
${dpr_calc} ${param} -b 30 >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -b 30 -adv >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -b 30 -dis >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -b 30 -elf >> ${result}
echo "" >> ${result}

# Case 3: -d 12 -ac 8 -b -30
${dpr_calc} ${param} -b -30 >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -b -30 -adv >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -b -30 -dis >> ${result}
echo "" >> ${result}
${dpr_calc} ${param} -b -30 -elf >> ${result}

echo "Comparing ${result} with ${dpr_sample}..."
if diff -q ${result} ${dpr_sample} > /dev/null 2>&1; then
  echo "Success: Output is identical."
  exit 0
else
  echo "Failure: Output differs. Manual checking recommended in case of testing error."
  exit 1
fi
