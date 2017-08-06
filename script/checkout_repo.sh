#!/bin/bash

SHELL_DIR=$(dirname `readlink -f $0`)

help()
{
    echo "Usage: $0 options"
    echo "-h: help"
    echo "-t: repo tag"
    echo "-b: repo branch"
}

check_branch_exist()
{
    branch=$1

    git branch -a | grep -E "remotes/origin/$branch$"
    ret=$?
    if [ $ret -ne 0 ];
    then
        echo "remote branch $branch not exist,"
	exit
    fi

    git branch | grep -E "$branch$"
    return $?
}

check_tag_exist()
{
    tag=$1

    git tag | grep -E "$tag$"
    ret=$?
    if [ $ret -ne 0 ];then
        echo "remote tag $tag not exist"
	exit
    fi
    
    # checkout tag branch exist
    git branch | grep -E "$tag$"
    return $?
}

checkout_tag()
{
    tag=$1

    check_tag_exist $tag
    if [ $? -eq 0 ];then
        # tag exist
        git checkout $tag
	if [ $? -ne 0 ];then
	    echo "Checkout existent tag error."
	fi
        git pull origin $tag
    else
	git checkout -b $tag $tag
	if [ $? -ne 0 ];then
	    echo "Checkout non-existent tag error."
	fi
    fi
}

checkout_branch()
{
    branch=$1
    check_branch_exist $branch
    if [ $? -eq 0 ];then
        # branch exist
        git checkout $branch
	if [ $? -ne 0 ];then
	    echo "Checkout existent branch error."
        fi	
    	git pull origin $branch
    else
        # branch not exist
	git checkout -b $branch origin/$branch
	if [ $? -ne 0 ];then
	    echo "Checkout non-existent branch error."
	fi 
    fi 
}

checkout()
{
    type=$1
    value=$2

    cd $SHELL_DIR
    repo_list=$(ls ./ | grep as)
    for repo in $repo_list;
    do
        cd $repo

    	if [ x"$type" == x"tag" ]; then
    	    checkout_tag $value
    	elif [ x"$type" == x"branch" ]; then
    	    checkout_branch $value
    	else
    	    echo "Checkout type error"
	    break
    	fi

	cd ..
    done

    cd $SHELL_DIR
}

while getopts ":b:t:h" opt;
do
    case $opt in
        h)
	    help
	    ;;
	t)
	    tag=$OPTARG
	    checkout "tag" $tag
	    ;;
	b)
	    branch=$OPTARG
	    checkout "branch" $branch
	    ;;
	?)
	    help
	    ;;
    esac
done
    
