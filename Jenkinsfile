pipeline {
    agent none
    options {
        parallelsAlwaysFailFast()
    }
    stages {
        stage('Prerequisite Stage') {
            agent {
                label "Master"
            }            
            steps {
                sh "mkdir -p thirdparty"
                sh "curl -L http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz > thirdparty/boost_1_59_0.tar.gz"
                sh "curl -L http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.7z > thirdparty/boost_1_59_0.7z"
                sh "curl -L http://sourceforge.net/projects/log4cplus/files/log4cplus-stable/1.2.0/log4cplus-1.2.0-rc5.tar.gz > thirdparty/log4cplus-1.2.0-rc5.tar.gz"
                sh "curl -L ftp://xmlsoft.org/libxml2/libxslt-1.1.21.tar.gz > thirdparty/libxslt-1.1.21.tar.gz"
                sh "curl -L ftp://xmlsoft.org/libxml2/libxml2-2.8.0.tar.gz > thirdparty/libxml2-2.8.0.tar.gz"
                stash includes: 'thirdparty/*', name: 'thirdparty'            
            }
        }
        stage('Parallel Build Stage') {
            parallel {
                stage('Linux Build') {
                    agent {
                        label "Linux"
                    }
                    steps {
                        unstash "thirdparty"
                        sh "cp thirdparty/* ./Projects/CPP/vendor"
                    }
                }
                stage('Windows Build') {
                    agent {
                        label "Windows"
                    }
                    steps {
                        unstash "thirdparty"
                        bat "copy thirdparty\\* .\\Projects\\CPP\\vendor\\*"
                    }
                }
                stage('Mac_OS_X_Intel Build') {
                    agent {
                        label "Mac_OS_X_Intel"
                    }
                    steps {
                        unstash "thirdparty"
                        sh "cp thirdparty/boost_1_59_0.tar.gz ./Projects/CPP/vendor"
                        sh "cp thirdparty/boost_1_59_0.7z ./Projects/CPP/vendor"
                        sh "cp thirdparty/log4cplus-1.2.0-rc5.tar.gz ./Projects/CPP/vendor"
                        sh "cp thirdparty/libxslt-1.1.21.tar.gz ./Projects/CPP/vendor"
                        sh "cp thirdparty/libxml2-2.8.0.tar.gz ./Projects/CPP/vendor"
                        sh "./Projects/CPP/jenkinsbuild-osx.sh"
                    }
                }
            }
        }
    }
}
