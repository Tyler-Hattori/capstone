#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/thattori/capstone/F1Tenth/velma/src/twist_to_ackermann"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/thattori/capstone/F1Tenth/velma/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/thattori/capstone/F1Tenth/velma/install/lib/python3/dist-packages:/home/thattori/capstone/F1Tenth/velma/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/thattori/capstone/F1Tenth/velma/build" \
    "/usr/bin/python3" \
    "/home/thattori/capstone/F1Tenth/velma/src/twist_to_ackermann/setup.py" \
     \
    build --build-base "/home/thattori/capstone/F1Tenth/velma/build/twist_to_ackermann" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/thattori/capstone/F1Tenth/velma/install" --install-scripts="/home/thattori/capstone/F1Tenth/velma/install/bin"
