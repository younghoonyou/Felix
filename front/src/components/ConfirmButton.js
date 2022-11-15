import React from 'react';

import '../App.css';

const ConfirmButton = (props) => {
  const { title, onClick } = props;
  return (
    <>
      <button type='submit' className='ConfirmButton' onClick={onClick}>
        {title}
      </button>
    </>
  );
};

export default ConfirmButton;
