from setuptools import Extension, setup

setup(
    ext_modules=[
        Extension(
            name="custom",  # as it would be imported
                               # may include packages/namespaces separated by `.`
            extra_compile_args = ["/std:c++latest"],
            sources=["module.cpp"], # all sources are compiled into a single binary file
        ),
    ]
)
