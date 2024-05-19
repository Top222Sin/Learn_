unset BOARD_TARGET
BOARD_TARGET=(X86_64 TOPEET ATK ANDROID)
function print_target_menu()
{
    echo "board target supported:"
    local i=1
    local choice
    for choice in ${BOARD_TARGET[@]}; do
        echo "    $i. $choice"
        i=$(($i+1))
    done
}

if [ "$1" != ""  ]; then
    if echo $1 | grep -q '[^0-9]'; then
        BOARD_NAME=`echo "$1" | tr "a-z" "A-Z"`
    else
        BOARD_NAME=${BOARD_TARGET[$1]}
    fi
fi

echo "$BOARD_NAME"

while [ 1 ]; do
    if [ "$BOARD_NAME" = "X86_64" ] ; then
        echo "X86_64"
        toolchain_file=toolchains/host.gcc.toolchain.cmake
        install_path=install
        break;
    elif [ "$BOARD_NAME" = "TOPEET"  ] ; then
        echo "TOPEET"
        TOOLCHAINS=/home/tool/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/
        export PATH=$TOOLCHAINS/bin:$PATH
        export PATH=$TOOLCHAINS/libexec/gcc/aarch64-none-linux-gnu/10.3.1:$PATH
        echo $PATH
        toolchain_file=toolchains/aarch64-none-linux-gnu.toolchain.cmake
        install_path=install
        break;
    elif [ "$BOARD_NAME" = "ATK"  ] ; then
        echo "ATK"
        TOOLCHAINS=/home/tool/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/
        export PATH=$TOOLCHAINS/bin:$PATH
        export PATH=$TOOLCHAINS/libexec/gcc/arm-none-linux-gnueabihf/9.2.1:$PATH
        toolchain_file=toolchains/arm-9.2-none-linux-gnueabihf.toolchain.cmake
        install_path=install
        break;
    elif [ "$BOARD_NAME" = "ANDROID"  ] ; then
        echo "ATK"
        TOOLCHAINS=/home/jyang/tools/android-ndk-r26c/toolchains/llvm/prebuilt/linux-x86_64
        export PATH=$TOOLCHAINS/bin:$PATH
        toolchain_file=/home/jyang/tools/android-ndk-r26c/build/cmake/android.toolchain.cmake
        install_path=install
        break;
    else
        print_target_menu
        read -p "Please choose target board: " cho

        if [ -z "$cho"  ] ; then
            sel=0
        elif (echo -n $cho | grep -q -e "^[0-9][0-9]*$") ; then
            if [ $cho -le ${#BOARD_TARGET[@]} -a $cho -ge 0  ] ; then
                sel=$cho
            else
                echo
                echo "Invalid choice!: $cho"
                continue
            fi
        else
            echo "Invalid choice!"
            continue
        fi
        BOARD_NAME=${BOARD_TARGET[$sel-1]}
    fi
done

BUILD_DIR=build
rm $BUILD_DIR -rf
mkdir -p $BUILD_DIR
cd $BUILD_DIR
mkdir -p $BOARD_NAME
cd $BOARD_NAME
cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_TOOLCHAIN_FILE=$toolchain_file \
    -Dopencv_DIR=ThirdLibs/OpenCV/install/lib/cmake/opencv5 \
    -Dbenchmark_DIR=ThirdLibs/benchmark/install/lib/cmake/benchmark \
    -Dgtest_DIR=ThirdLibs/gtest/install/lib/cmake/GTest \
    ../..
make -j8
# make cppcheck
# make valgrind
cmake --install . --prefix install >> install_log
