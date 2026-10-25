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
                sh "curl -k -L https://download.gnome.org/sources/libxslt/1.1/libxslt-1.1.22.tar.gz > libxslt-1.1.22.tar.gz"
                sh "curl -k -L https://download.gnome.org/sources/libxslt/1.1/libxslt-1.1.34.tar.xz > libxslt-1.1.34.tar.xz"
                sh "curl -k -L https://gitlab.gnome.org/GNOME/libxslt/-/archive/v1.1.38/libxslt-v1.1.38.tar.gz > libxslt-v1.1.38.tar.gz"
                sh "curl -k -L https://download.gnome.org/sources/libxml2/2.8/libxml2-2.8.0.tar.xz > libxml2-2.8.0.tar.xz"
                sh "xz -d libxml2-2.8.0.tar.xz"
                sh "gzip libxml2-2.8.0.tar"
                sh "xz -d libxslt-1.1.34.tar.xz"
                sh "gzip libxslt-1.1.34.tar"
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
                        sh "cp thirdparty/* ./Projects/lbdmf/vendor"
                    }
                }
                stage('Windows Build') {
                    agent {
                        label "Windows"
                    }
                    steps {
                        unstash "thirdparty"
                        bat "copy thirdparty\\* .\\Projects\\lbdmf\\vendor\\*"
                    }
                }
                stage('Mac_OS_X_Intel Build') {
                    agent {
                        label "Mac_OS_X_Intel"
                    }
                    steps {
                        unstash "thirdparty"
                        sh "cp thirdparty/* ./Projects/lbdmf/vendor"
                        sh "./Projects/lbdmf/jenkinsbuild-osx.sh"
                    }
                }
                stage('Mac_OS_X_Arm Build') {
                    agent {
                        label "Mac_OS_X_Arm"
                    }
                    steps {
                        unstash "thirdparty"
                        sh "cp thirdparty/* ./Projects/lbdmf/vendor"
                        sh "./Projects/lbdmf/jenkinsbuild-osxarm.sh"
                    }
                }
            }
        }
    }
}
